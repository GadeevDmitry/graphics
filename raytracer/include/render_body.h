#ifndef RENDER_BODY_H
#define RENDER_BODY_H

#include "material.h"
#include "ray.h"
#include "vec3d.h"

//==================================================================================================

class render_body_t
{
public:
    material_t material;

    explicit render_body_t(const material_t &material_ = material_t()):
    material(material_)
    {}

    virtual ~render_body_t() {}

    virtual bool  get_intersection(const ray_t &ray, vec3d &intersect_pt) const = 0;
    virtual vec3d get_normal      (const vec3d &pt) const = 0;
};

#endif // RENDER_BODY_H
