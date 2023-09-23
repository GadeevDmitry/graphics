#ifndef SCENE_H
#define SCENE_H

#include "circle.h"
#include "vec2d.h"
#include "segment.h"
#include "molecule.h"
#include "rectangle.h"

#include "vector/vector.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class scene_t
{
private:
    vector       molecules;
    const double molecule_size;

    static void delete_molecule(void *const molecule)
    {
        delete *(molecule_t **) molecule;
    }

    void refresh_by_molecule_blows(const double frame_time,       bool *is_molecule_interaction, const size_t initial_size);
    void refresh_by_segment_blows (const double frame_time, const bool *is_molecule_interaction, const size_t initial_size);
    void refresh_piston           (const double frame_time);

    friend void molecule_interaction_heavy_heavy(scene_t &scene, const double hit_time, const molecule_t &heavy_1, const molecule_t &heavy_2);
    friend void molecule_interaction_heavy_light(scene_t &scene, const double hit_time, const molecule_t &heavy  , const molecule_t &light  );
    friend void molecule_interaction_light_light(scene_t &scene, const double hit_time, const molecule_t &light_1, const molecule_t &light_2);

public:
    const rectangle_t walls;

    segment_t piston;
    vec2d     piston_speed;

    explicit scene_t(const rectangle_t &walls_,

                     const double molecule_size_ = 3,
                     const size_t molecules_num_ = 50,

                     const segment_t &piston_       = segment_t(),
                     const vec2d     &piston_speed_ = vec2d()):
    molecule_size(molecule_size_),
    walls        (walls_),

    piston      (piston_),
    piston_speed(piston_speed_)
    {
        vector_ctor(&molecules, sizeof(molecule_t *), nullptr, delete_molecule);

        for (size_t ind = 0; ind < molecules_num_; ++ind)
        {
            int  walls_width  = (int) (walls_.ru_corner.x - walls_.ld_corner.x - molecule_size_);
            int  walls_height = (int) (walls_.ru_corner.y - walls_.ld_corner.y - molecule_size_);
            vec2d ld_molecule = walls_.ld_corner + vec2d(molecule_size_, molecule_size_) / 2;

            vec2d center = vec2d(ld_molecule.x + abs(rand()) % walls_width,
                                 ld_molecule.y + abs(rand()) % walls_height);
            vec2d speed  = vec2d(rand() % 50, rand() % 50);

            heavy_molecule_t *instance = new heavy_molecule_t(2, circle_t(center, molecule_size_ / 2), speed);
            vector_push_back(&molecules, &instance);
        }
    }

    ~scene_t()
    {
        vector_dtor(&molecules);
    }

    void draw   (sf::RenderWindow &wnd) const;
    void refresh(const double frame_time);
};

#endif // SCENE_H
