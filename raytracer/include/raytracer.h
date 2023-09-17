#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vec3d.h"
#include "color.h"
#include "scene.h"

//==================================================================================================

class raytracer_t
{
private:
    color_t ambient;
    vec3d   view_pt;

    color_t ray_cast      (const vec3d &start_pt, const vec3d &target_pt, const int depth) const;
    color_t self_component(const vec3d &start_pt, const vec3d &hit_pt, const render_body_t &hit_body) const;

public:
    scene_t scene;

    raytracer_t(const color_t &ambient_, const vec3d &view_pt_):
    scene(),
    ambient(ambient_),
    view_pt(view_pt_)
    {}

    color_t raytrace(const vec3d &target_pt, const int depth = 4) const
    {
        return ray_cast(view_pt, target_pt, depth);
    }
};

#endif // RAYTRACER_H
