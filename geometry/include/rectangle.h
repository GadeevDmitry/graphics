#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vec2d.h"

//==================================================================================================

class rectangle_t
{
public:
    vec2d ld_corner;
    vec2d ru_corner;

    explicit rectangle_t(const vec2d &ld_corner_ = vec2d(), const vec2d &ru_corner_ = vec2d()):
    ld_corner(ld_corner_),
    ru_corner(ru_corner_)
    {}
};

#endif // RECTANGLE_H
