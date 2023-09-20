#ifndef CIRCLE_H
#define CIRCLE_H

#include "vec2d.h"

//==================================================================================================

class circle_t
{
public:
    vec2d  center;
    double radius;

    explicit circle_t(const vec2d &center_, const double radius_):
    center(center_),
    radius(radius_)
    {}
};

#endif // CIRCLE_H
