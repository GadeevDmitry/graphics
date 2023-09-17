#include <stdio.h>
#include <stdlib.h>

#include "ray.h"
#include "render_body.h"
#include "scene.h"

#include "vector/vector.h"

//==================================================================================================

bool scene_t::get_ray_hitpoint(const ray_t &ray, vec3d &hit_pt, render_body_t* &hit_body) const
{
    bool   is_hitted = false;
    double ray_len2  = NAN;

    for (render_body_t **body_ = (render_body_t **) vector_begin(&bodies);
                         body_ != (render_body_t **) vector_end (&bodies);
                       ++body_)
    {
        render_body_t *body = *body_;
        vec3d hit_cur_pt;

        if (!body->get_intersection(ray, hit_cur_pt))
            continue;

        double cur_ray_len2 = (hit_cur_pt - ray.get_start()).len2();

        if (!is_hitted || ray_len2 > cur_ray_len2)
        {
            is_hitted = true;
            ray_len2  = cur_ray_len2;

            hit_pt   = hit_cur_pt;
            hit_body = body;
        }
    }

    return is_hitted;
}
