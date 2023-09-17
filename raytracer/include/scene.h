#ifndef SCENE_H
#define SCENE_H

#include "lighter.h"
#include "render_body.h"

#include <vector/vector.h>

//==================================================================================================

class raytracer_t;

class scene_t
{
private:
    vector lighters;
    vector bodies;

    bool get_ray_hitpoint(const ray_t &ray, vec3d &hit_pt, render_body_t* &hit_body) const;
    friend raytracer_t;

public:
    explicit scene_t()
    {
        vector_ctor(&lighters, sizeof(lighter_t *));
        vector_ctor(&bodies  , sizeof(render_body_t *));
    }

    ~scene_t()
    {
        vector_dtor(&lighters);
        vector_dtor(&bodies);
    }

    void add_lighter    (const lighter_t     *added) { vector_push_back(&lighters, &added); }
    void add_render_body(const render_body_t *added) { vector_push_back(&bodies  , &added); }
};

#endif // SCENE_H
