#include <stdio.h>
#include <stdlib.h>

#include "scene.h"
#include "molecule_manager.h"

#include "array/array.h"

//==================================================================================================

molecule_manager_t::molecule_manager_t(const double molecule_size_,
                                       const size_t molecules_num_,

                                       const vec2d &area_size_):
molecule_size(molecule_size_),
molecules_tex()
{
    log_verify(molecule_size_ > 0, ;);
    log_verify(area_size_.x   > 0, ;);
    log_verify(area_size_.y   > 0, ;);

    vector_ctor(&molecules, sizeof(molecule_t *), nullptr, delete_molecule);

    light_molecule_t *molecule = new light_molecule_t(circle_t(vec2d(200, 200), 5), vec2d(50, 0));
    vector_push_back(&molecules, &molecule);
/*
    for (size_t ind = 0; ind < molecules_num_; ++ind)
    {
        vec2d molecule_area_ld =              vec2d(molecule_size_, molecule_size_) / 2;
        vec2d molecule_area_ru = area_size_ - vec2d(molecule_size_, molecule_size_) / 2;

        int area_width  = (int) (molecule_area_ru.x - molecule_area_ld.x);
        int area_height = (int) (molecule_area_ru.y - molecule_area_ld.y);

        vec2d center(molecule_area_ld.x + abs(rand()) % area_width,
                     molecule_area_ld.y + abs(rand()) % area_height);

        vec2d speed(rand() % 50, rand() % 50);

        light_molecule_t *molecule = new light_molecule_t(circle_t(center, molecule_size_ / 2), speed);
        vector_push_back(&molecules, &molecule);
    }
*/
    molecules_tex.create((unsigned) area_size_.x, (unsigned) area_size_.y);
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::draw()
{
    if (molecules.size == 0) return;

    molecules_tex.clear();

    for (molecule_t **molecule = (molecule_t **) vector_begin(&molecules);
                      molecule != vector_end(&molecules);
                    ++molecule)
    {
        (*molecule)->draw(molecules_tex);
    }

    molecules_tex.display();
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::refresh(const double frame_time, const scene_t &scene)
{
    size_t initial_size = molecules.size;
    array  molecules_refresh_status = {};

    MOLECULE_REFRESH_STATUS_TYPE unchanged_ = MOLECULE_UNCHANGED;
    array_ctor(&molecules_refresh_status, initial_size, sizeof(MOLECULE_REFRESH_STATUS_TYPE));
    array_init(&molecules_refresh_status, &unchanged_);

    refresh_by_molecule_collisions(frame_time, initial_size, &molecules_refresh_status);
    refresh_by_wall_collisions    (frame_time, initial_size, &molecules_refresh_status, scene);

    for (int ind = (int) initial_size - 1; ind >= 0; --ind)
    {
        MOLECULE_REFRESH_STATUS_TYPE status = *(MOLECULE_REFRESH_STATUS_TYPE *) array_get(&molecules_refresh_status, (size_t) ind);
        molecule_t &molecule = **(molecule_t **) vector_get(&molecules, (size_t) ind);

        switch (status)
        {
            case MOLECULE_UPDATED  : break;
            case MOLECULE_UNCHANGED: molecule.refresh(frame_time); break;
            case MOLECULE_DESTROYED: vector_erase(&molecules, (size_t) ind); break;

            default: log_assert(false && "undefined MOLECULE_REFRESH_STATUS_TYPE]\n");
        }
    }

    array_dtor(&molecules_refresh_status);
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::refresh_by_molecule_collisions(const double frame_time, const size_t initial_size, array *const molecules_refresh_status)
{
    for (size_t l = 0; l < initial_size; ++l)
    {
        if (*(MOLECULE_REFRESH_STATUS_TYPE *) array_get(molecules_refresh_status, l) != MOLECULE_UNCHANGED)
            continue;

        for (size_t r = l + 1; r < initial_size; ++r)
        {
            if (*(MOLECULE_REFRESH_STATUS_TYPE *) array_get(molecules_refresh_status, r) != MOLECULE_UNCHANGED)
                continue;

            molecule_t &left  = **(molecule_t **) vector_get(&molecules, l);
            molecule_t &right = **(molecule_t **) vector_get(&molecules, r);

            double hit_time = 0;
            if (left.try_hit_circle(frame_time, right.shape, right.speed, hit_time))
            {
                molecule_interaction(hit_time, left , *(MOLECULE_REFRESH_STATUS_TYPE *) array_get(molecules_refresh_status, l),
                                               right, *(MOLECULE_REFRESH_STATUS_TYPE *) array_get(molecules_refresh_status, r));
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::refresh_by_wall_collisions(const double frame_time, const size_t initial_size,
                                                    array *const molecules_refresh_status, const scene_t &scene)
{
    MOLECULE_REFRESH_STATUS_TYPE updated_   = MOLECULE_UPDATED;
    MOLECULE_REFRESH_STATUS_TYPE unchanged_ = MOLECULE_UNCHANGED;

    for (size_t ind = 0; ind < initial_size; ++ind)
    {
        if (*(MOLECULE_REFRESH_STATUS_TYPE *) array_get(molecules_refresh_status, ind) != MOLECULE_UNCHANGED)
            continue;

        molecule_t &cur = **(molecule_t **) vector_get(&molecules, ind);

        vec2d walls_lu_corner(scene.walls.ld_corner.x, scene.walls.ru_corner.y);
        vec2d walls_rd_corner(scene.walls.ru_corner.x, scene.walls.ld_corner.y);
/*
        printf("walls:  (%lg, %lg) -> (%lg, %lg)\n", scene.walls.ld_corner.x, scene.walls.ld_corner.y,
                                                    scene.walls.ru_corner.x, scene.walls.ru_corner.y);

        printf("center: (%lg, %lg)\n", cur.shape.center.x, cur.shape.center.y);
*/
        array_set(molecules_refresh_status, ind, &updated_);

        if (cur.try_hit_segment(frame_time, scene.piston)) continue;
        if (cur.try_hit_segment(frame_time, segment_t(scene.walls.ld_corner, walls_lu_corner))) continue;
        if (cur.try_hit_segment(frame_time, segment_t(walls_lu_corner, scene.walls.ru_corner))) continue;
        if (cur.try_hit_segment(frame_time, segment_t(scene.walls.ru_corner, walls_rd_corner))) continue;
        if (cur.try_hit_segment(frame_time, segment_t(walls_rd_corner, scene.walls.ld_corner))) continue;

        array_set(molecules_refresh_status, ind, &unchanged_);
    }
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::molecule_interaction(const double hit_time, molecule_t &m1, MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                     molecule_t &m2, MOLECULE_REFRESH_STATUS_TYPE &status_2)
{
    typedef void (molecule_manager_t::*molecule_interaction_type_type)(const double hit_time,
                                                                       molecule_t &m1, MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                       molecule_t &m2, MOLECULE_REFRESH_STATUS_TYPE &ststus_2);

    static molecule_interaction_type_type interaction_table[MOLECULE_TYPE_MAX][MOLECULE_TYPE_MAX] =
        {{&molecule_manager_t::molecule_interaction_heavy_heavy, &molecule_manager_t::molecule_interaction_heavy_light},
         {&molecule_manager_t::molecule_interaction_heavy_light, &molecule_manager_t::molecule_interaction_light_light}};

    (this->*interaction_table[m1.type][m2.type])(hit_time, m1, status_1, m2, status_2);
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::molecule_interaction_heavy_heavy(const double hit_time, molecule_t &heavy_1, MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                                 molecule_t &heavy_2, MOLECULE_REFRESH_STATUS_TYPE &status_2)
{
    vec2d    hit_point  = heavy_1.shape.center + hit_time * heavy_1.speed;
    unsigned sum_weight = heavy_1.weight + heavy_2.weight;

    vec2d  light_speed(50, 50);
    double rotate_unit = 360.0 / sum_weight;

    for (size_t ind = 0; ind < sum_weight; ++ind)
    {
        light_molecule_t *instance = new light_molecule_t(circle_t(hit_point, heavy_1.shape.radius), light_speed);
        vector_push_back(&molecules, &instance);

        light_speed.rotate(rotate_unit);
    }

    status_1 = MOLECULE_DESTROYED;
    status_2 = MOLECULE_DESTROYED;
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::molecule_interaction_heavy_light(const double hit_time, molecule_t &heavy, MOLECULE_REFRESH_STATUS_TYPE &status_heavy,
                                                                                 molecule_t &light, MOLECULE_REFRESH_STATUS_TYPE &status_light)
{
    (void) light;

    vec2d hit_point = heavy.shape.center + hit_time * heavy.speed;

    heavy.weight++;
    heavy.shape.center = hit_point;

    status_heavy = MOLECULE_UPDATED;
    status_light = MOLECULE_UNCHANGED;
}

//--------------------------------------------------------------------------------------------------

void molecule_manager_t::molecule_interaction_light_light(const double hit_time, molecule_t &light_1, MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                                 molecule_t &light_2, MOLECULE_REFRESH_STATUS_TYPE &status_2)
{
    vec2d hit_point = light_1.shape.center + hit_time * light_1.speed;
    vec2d res_speed = (light_1.speed + light_2.speed) / 2;

    heavy_molecule_t *heavy = new heavy_molecule_t(2, circle_t(hit_point, light_1.shape.radius), res_speed);
    vector_push_back(&molecules, &heavy);

    status_1 = MOLECULE_DESTROYED;
    status_2 = MOLECULE_DESTROYED;
}
