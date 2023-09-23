#ifndef CIRCLE_H
#define CIRCLE_H

#include "vec2d.h"
#include "algorithm/algorithm.h"

//==================================================================================================

class circle_t
{
public:
    vec2d  center;
    double radius;

    explicit circle_t(const vec2d &center_ = vec2d(), const double radius_ = 0):
    center(center_),
    radius(radius_)
    {}

    bool is_inside    (const vec2d &pt) { return (pt - center).len2() <= radius*radius; }
    bool is_on_surface(const vec2d &pt) { return dblcmp((pt - center).len2(), radius*radius) == 0; }
};

#endif // CIRCLE_H
