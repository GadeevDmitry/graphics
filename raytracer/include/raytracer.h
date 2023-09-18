#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "material.h"
#include "render_body.h"
#include "vec3d.h"
#include "color.h"
#include "scene.h"

//==================================================================================================

class raytracer_t
{
private:
    color_t ambient;

    typedef struct hit_context_t
    {
        vec3d hit_pt;
        vec3d view_pt;
        vec3d view_dir;
        vec3d reflect_dir;
        vec3d hit_norm;

        material_t &material;

        explicit hit_context_t(const ray_t &ray, const vec3d &hit_pt, const vec3d &hit_norm, render_body_t* &hit_body);
        explicit hit_context_t(const hit_context_t &hit_context):
        hit_pt(hit_context.hit_pt),
        view_pt(hit_context.view_pt),
        view_dir(hit_context.view_dir),
        reflect_dir(hit_context.reflect_dir),
        hit_norm(hit_context.hit_norm),
        material(hit_context.material)
        {}

        hit_context_t &operator =(const hit_context_t &hit_context) { return (*this) = hit_context; }
    }
    hit_context_t;

    color_t self_component   (const hit_context_t &hit_context) const;
    color_t reflect_component(const hit_context_t &hit_context, const int depth) const;

public:
    scene_t scene;

    raytracer_t(const color_t &ambient_):
    ambient(ambient_),
    scene()
    {}

    color_t raytrace(const ray_t &ray, const int depth = 4) const;
};

#endif // RAYTRACER_H
