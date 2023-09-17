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
    direction(direction_)
    {}

    vec3d get_start()     const { return start; }
    vec3d get_direction() const { return direction; }
};

#endif // RAY_H
