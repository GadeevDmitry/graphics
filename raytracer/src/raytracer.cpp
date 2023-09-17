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
#include "vector/vector.h"

//==================================================================================================

color_t raytracer_t::ray_cast(const vec3d &start_pt, const vec3d &target_pt, const int depth) const
{
    if (depth == 0) return ambient;

    vec3d          hit_pt;
    render_body_t *hit_body = nullptr;

    if (!scene.get_ray_hitpoint(ray_t(start_pt, target_pt - start_pt), hit_pt, hit_body))
        return ambient;

    return self_component(start_pt, hit_pt, *hit_body) + ambient * hit_body->get_material().own_col;
}

//--------------------------------------------------------------------------------------------------

color_t raytracer_t::self_component(const vec3d &start_pt, const vec3d &hit_pt, const render_body_t &hit_body) const
{
    color_t res = color_t(0, 0, 0);

    if (dblcmp(hit_body.get_material().get_diff_coeff() , 0) == 0 &&
        dblcmp(hit_body.get_material().get_spec_degree(), 0) == 0)
        return res;

    for (lighter_t **lighter_ = (lighter_t **) vector_begin(&scene.lighters);
                     lighter_ != (lighter_t **) vector_end (&scene.lighters);
                   ++lighter_)
    {
        lighter_t *lighter = *lighter_;

        vec3d          light_hit_pt;
        render_body_t *light_hit_body = nullptr;
        vec3d          lighter_pos    = lighter->get_pos();

        scene.get_ray_hitpoint(ray_t(lighter_pos, hit_pt - lighter_pos), light_hit_pt, light_hit_body);
        if (light_hit_pt != hit_pt) continue;

        vec3d light_dir     = (lighter_pos - hit_pt)                              .get_normalization();
        vec3d view_dir      = (start_pt - hit_pt)                                 .get_normalization();
        vec3d hit_pt_norm   = hit_body.get_normal(hit_pt)                         .get_normalization();
        vec3d reflected_dir = (2*(hit_pt_norm, light_dir)*hit_pt_norm - light_dir).get_normalization();

        double cur_diff_coeff = (light_dir, hit_pt_norm);
        double cur_spec_coeff = (view_dir , reflected_dir);

        cur_diff_coeff = (cur_diff_coeff > 0) ? cur_diff_coeff : 0;
        cur_spec_coeff = (cur_spec_coeff > 0) ? pow(cur_spec_coeff, hit_body.get_material().get_spec_degree()) : 0;

        res += hit_body.get_material().get_diff_coeff() * cur_diff_coeff * lighter->get_own_col() * hit_body.get_material().own_col;
        res +=                                            cur_spec_coeff * lighter->get_own_col();
    }

    return res;
}
