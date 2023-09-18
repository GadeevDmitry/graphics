#include <cmath>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "color.h"
#include "lighter.h"
#include "material.h"
#include "raytracer.h"
#include "render_body.h"
#include "vec3d.h"
#include "vector/vector.h"

//==================================================================================================

color_t raytracer_t::raytrace(const ray_t &ray, const int depth) const
{
    if (depth == 0) return ambient;

    vec3d          hit_pt;
    render_body_t *hit_body = nullptr;

    if (!scene.get_ray_hitpoint(ray, hit_pt, hit_body))
        return ambient;

    hit_context_t hit_context(ray, hit_pt, hit_body->get_normal(hit_pt), hit_body);

    return self_component   (hit_context) +
           reflect_component(hit_context, depth) + ambient * hit_context.material.own_col;
}

//--------------------------------------------------------------------------------------------------

color_t raytracer_t::self_component(const hit_context_t &hit_context) const
{
    color_t res(0, 0, 0);

    if (dblcmp(hit_context.material.diff_coeff, 0) == 0 &&
        dblcmp(hit_context.material.spec_degree, 0) == 0)
        return res;

    for (lighter_t **lighter_ = (lighter_t **) vector_begin(&scene.lighters);
                     lighter_ != (lighter_t **) vector_end (&scene.lighters);
                   ++lighter_)
    {
        lighter_t *lighter     = *lighter_;
        ray_t      lighter_ray = ray_t(lighter->get_pos(), hit_context.hit_pt - lighter->get_pos());

        vec3d          light_hit_pt;
        render_body_t *light_hit_body = nullptr;
        scene.get_ray_hitpoint(lighter_ray, light_hit_pt, light_hit_body);
        if (light_hit_pt != hit_context.hit_pt) continue;

        vec3d lighter_reflected_dir = lighter_ray.get_reflected_dir(hit_context.hit_norm);

        double diff_coeff = (-lighter_ray.get_dir(), hit_context.hit_norm);
        double spec_coeff = (hit_context.view_dir, lighter_reflected_dir);

        diff_coeff = (diff_coeff > 0) ? diff_coeff : 0;
        spec_coeff = (spec_coeff > 0) ? pow(spec_coeff, hit_context.material.spec_degree) : 0;

        res += hit_context.material.diff_coeff * diff_coeff * lighter->get_own_col() * hit_context.material.own_col;
        res +=                                   spec_coeff * lighter->get_own_col();
    }

    return res;
}

//--------------------------------------------------------------------------------------------------

color_t raytracer_t::reflect_component(const hit_context_t &hit_context, const int depth) const
{
    if (dblcmp(hit_context.material.refl_coeff, 0) == 0)
        return color_t(0, 0, 0);

    return hit_context.material.refl_coeff * raytrace(ray_t(hit_context.hit_pt, hit_context.reflect_dir), depth - 1);
}

//--------------------------------------------------------------------------------------------------

raytracer_t::hit_context_t::hit_context_t(const ray_t &ray_, const vec3d &hit_pt_, const vec3d &hit_norm_, render_body_t* &hit_body_):
hit_pt(hit_pt_),
view_pt(ray_.get_start()),
view_dir(-ray_.get_dir()),
reflect_dir(ray_.get_reflected_dir(hit_norm_)),
hit_norm(hit_norm_.get_normalization()),
material(hit_body_->material)
{}
