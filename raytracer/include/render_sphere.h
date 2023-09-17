#ifndef RENDER_SPHERE_H
#define RENDER_SPHERE_H

#include "material.h"
#include "ray.h"
#include "render_body.h"
#include "vec3d.h"

//==================================================================================================

class render_sphere_t: public render_body_t
{
public:
    vec3d  center;
    double radius;

    explicit render_sphere_t(const material_t &material_, const vec3d &center_, const double radius_):
    render_body_t(material_),
    center(center_),
    radius(radius_)
    {}

    ~render_sphere_t() {}

    bool  get_intersection(const ray_t &ray, vec3d &intersect_pt) const;
    vec3d get_normal      (const vec3d &pt) const { return pt - center; };
    bool  is_on_surface   (const vec3d &pt) const;
};

#endif // RENDER_SPHERE_H
