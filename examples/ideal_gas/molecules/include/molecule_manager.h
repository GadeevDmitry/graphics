#ifndef MOLECULE_MANAGER_H
#define MOLECULE_MANAGER_H

#include "molecule.h"

#include "array/array.h"
#include "vector/vector.h"

//==================================================================================================

typedef class scene_t scene_t;

//--------------------------------------------------------------------------------------------------

class molecule_manager_t
{
private:
    enum MOLECULE_REFRESH_STATUS_TYPE
    {
        MOLECULE_UPDATED,
        MOLECULE_UNCHANGED,
        MOLECULE_DESTROYED,
    };

    vector            molecules;
    sf::RenderTexture molecules_tex;
    const double      molecule_size;

    rectangle_t reactor;
    segment_t   piston;

    static void delete_molecule(void *const molecule)
    {
        delete *(molecule_t **) molecule;
    }

    void refresh_by_molecule_collisions(const double frame_time, const size_t initial_size, array *const molecules_refresh_status);
    void refresh_by_wall_collisions    (const double frame_time, const size_t initial_size, array *const molecules_refresh_status);

    void molecule_interaction            (const double hit_time, molecule_t &m1     , MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                 molecule_t &m2     , MOLECULE_REFRESH_STATUS_TYPE &status_2);

    void molecule_interaction_heavy_light(const double hit_time, molecule_t &heavy  , MOLECULE_REFRESH_STATUS_TYPE &status_heavy,
                                                                 molecule_t &light  , MOLECULE_REFRESH_STATUS_TYPE &status_lights);

    void molecule_interaction_light_heavy(const double hit_time, molecule_t &light  , MOLECULE_REFRESH_STATUS_TYPE &status_light,
                                                                 molecule_t &heavy  , MOLECULE_REFRESH_STATUS_TYPE &status_heavy);

    void molecule_interaction_heavy_heavy(const double hit_time, molecule_t &heavy_1, MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                 molecule_t &heavy_2, MOLECULE_REFRESH_STATUS_TYPE &status_2);

    void molecule_interaction_light_light(const double hit_time, molecule_t &light_1, MOLECULE_REFRESH_STATUS_TYPE &status_1,
                                                                 molecule_t &light_2, MOLECULE_REFRESH_STATUS_TYPE &status_2);

public:
    explicit molecule_manager_t(const double molecule_size_, const size_t molecules_num_, const vec2d &reactor_size_);
    ~molecule_manager_t() { vector_dtor(&molecules); }

    const sf::Texture &get_texture() const { return molecules_tex.getTexture(); }

    void draw();
    void refresh(const double frame_time);
};

#endif // MOLECULE_MANAGER_H
