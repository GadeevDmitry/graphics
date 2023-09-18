#ifndef RAY_H
#define RAY_H

#include "vec3d.h"
#include "color.h"

//==================================================================================================

class ray_t
{
private:
    vec3d start;
    vec3d direction;

public:

    explicit ray_t(const vec3d &start_, const vec3d &direction_):
    start(start_),
    direction(direction_.get_normalization())
    {}

    vec3d get_dir  () const { return direction; }
    vec3d get_start() const { return start;     }

    vec3d get_reflected_dir(const vec3d &hit_normal_) const
    {
        vec3d hit_normal     = hit_normal_.get_normalization();
        vec3d reflacted_dir  = 2*(hit_normal, -direction)*hit_normal + direction;

        return reflacted_dir.get_normalization();
    }
};

#endif // RAY_H
