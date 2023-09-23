#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "scene.h"
#include "circle.h"
#include "molecule.h"
#include "distance.h"

#include "vector/vector.h"

//==================================================================================================

static void molecule_interaction(scene_t &scene, const double hit_time, const molecule_t &m1, const molecule_t &m2);

//==================================================================================================

void scene_t::draw(sf::RenderWindow &wnd) const
{
    draw_hollow_rectangle(walls , wnd, sf::Color::Green);
    draw_segment         (piston, wnd, sf::Color::Magenta);

    if (molecules.size == 0) return;

    molecule_t **molecule = (molecule_t **) vector_begin(&molecules);
    for (; molecule != vector_end(&molecules); ++molecule)
    {
        (*molecule)->draw(wnd);
    }
}

//--------------------------------------------------------------------------------------------------

void scene_t::refresh(const double frame_time)
{
    if (molecules.size == 0)
    {
        refresh_piston(frame_time);
        return;
    }

    size_t initial_size = molecules.size;
    bool is_molecule_interaction[initial_size];

    refresh_by_molecule_blows(frame_time, is_molecule_interaction, initial_size);
    refresh_by_segment_blows (frame_time, is_molecule_interaction, initial_size);

    for (int ind = (int) initial_size - 1; ind >= 0; --ind)
    {
        if (is_molecule_interaction[ind])
            vector_erase(&molecules, ind);
    }

    refresh_piston(frame_time);
}

//--------------------------------------------------------------------------------------------------

void scene_t::refresh_by_molecule_blows(const double frame_time, bool *is_molecule_interaction, const size_t initial_size)
{
    for (size_t ind = 0; ind < initial_size; ++ind)
        is_molecule_interaction[ind] = false;

    for (size_t l = 0; l < initial_size; ++l)
    {
        if (is_molecule_interaction[l]) continue;
        molecule_t &left = **(molecule_t **) vector_get(&molecules, l);

        for (size_t r = l + 1; r < initial_size; ++r)
        {
            if (is_molecule_interaction[r]) continue;
            molecule_t &right = **(molecule_t **) vector_get(&molecules, r);

            double hit_time = 0;
            if (left.try_hit_circle(frame_time, right.shape, right.speed, hit_time))
            {
                molecule_interaction(*this, hit_time, left, right);
                is_molecule_interaction[l] = true;
                is_molecule_interaction[r] = true;
                break;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

void scene_t::refresh_by_segment_blows(const double frame_time, const bool *is_molecule_interaction, const size_t initial_size)
{
    vec2d walls_lu_corner(walls.ld_corner.x, walls.ru_corner.y);
    vec2d walls_rd_corner(walls.ru_corner.x, walls.ld_corner.y);

    for (size_t ind = 0; ind < initial_size; ++ind)
    {
        if (is_molecule_interaction[ind] == false)
        {
            molecule_t &cur = **(molecule_t **) vector_get(&molecules, ind);

            if (cur.try_hit_segment(frame_time, piston                                     , piston_speed)) continue;
            if (cur.try_hit_segment(frame_time, segment_t(walls.ld_corner, walls_lu_corner), vec2d(0, 0) )) continue;
            if (cur.try_hit_segment(frame_time, segment_t(walls_lu_corner, walls.ru_corner), vec2d(0, 0) )) continue;
            if (cur.try_hit_segment(frame_time, segment_t(walls.ru_corner, walls_rd_corner), vec2d(0, 0) )) continue;
            if (cur.try_hit_segment(frame_time, segment_t(walls_rd_corner, walls.ld_corner), vec2d(0, 0) )) continue;

            cur.refresh(frame_time);
        }
    }
}

//--------------------------------------------------------------------------------------------------

void scene_t::refresh_piston(const double frame_time)
{
    segment_t next_frame_piston = piston + frame_time * piston_speed;

    segment_t upper_wall(vec2d(walls.ld_corner.x, walls.ru_corner.y), walls.ru_corner);
    upper_wall -= 3*vec2d(0, molecule_size);

    if (next_frame_piston.endpoint_1.y > upper_wall.endpoint_1.y)
    {
        piston_speed = vec2d(0, 0);
        return;
    }

    piston = next_frame_piston;
}

//--------------------------------------------------------------------------------------------------

void molecule_interaction_heavy_heavy(scene_t &scene, const double hit_time, const molecule_t &heavy_1, const molecule_t &heavy_2)
{
    vec2d    hit_point  = heavy_1.shape.center + hit_time * heavy_1.speed;
    unsigned sum_weight = heavy_1.weight + heavy_2.weight;

    vec2d  light_speed(50, 50);
    double rotate_unit = 360.0 / sum_weight;

    for (size_t ind = 0; ind < sum_weight; ++ind)
    {
        light_molecule_t *instance = new light_molecule_t(circle_t(hit_point, heavy_1.shape.radius), light_speed);
        vector_push_back(&scene.molecules, &instance);

        light_speed.rotate(rotate_unit);
    }
}

//--------------------------------------------------------------------------------------------------

void molecule_interaction_heavy_light(scene_t &scene, const double hit_time, const molecule_t &heavy, const molecule_t &light)
{
    (void) light;

    vec2d hit_point = heavy.shape.center + hit_time * heavy.speed;
    heavy_molecule_t *heavier = new heavy_molecule_t(heavy.weight + 1,
                                                     circle_t(hit_point, heavy.shape.radius),
                                                     heavy.speed);
    vector_push_back(&scene.molecules, &heavier);
}

//--------------------------------------------------------------------------------------------------

void molecule_interaction_light_light(scene_t &scene, const double hit_time, const molecule_t &light_1, const molecule_t &light_2)
{
    vec2d hit_point = light_1.shape.center + hit_time * light_1.speed;
    vec2d res_speed = (light_1.speed + light_2.speed) / 2;

    heavy_molecule_t *heavy = new heavy_molecule_t(2, circle_t(hit_point, light_1.shape.radius), res_speed);
    vector_push_back(&scene.molecules, &heavy);
}

//--------------------------------------------------------------------------------------------------

static void molecule_interaction(scene_t &scene, const double hit_time, const molecule_t &m1, const molecule_t &m2)
{
    typedef void (*molecule_interaction_type_type)(scene_t &scene, const double hit_time,
                                                   const molecule_t &type_1, const molecule_t &type_2);

    static molecule_interaction_type_type interaction_table[MOLECULE_TYPE_MAX][MOLECULE_TYPE_MAX] =
        {{molecule_interaction_heavy_heavy, molecule_interaction_heavy_light},
         {molecule_interaction_heavy_light, molecule_interaction_light_light}};

    interaction_table[m1.type][m2.type](scene, hit_time, m1, m2);
}
