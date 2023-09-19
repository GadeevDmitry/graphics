#ifndef COORD_SYSTEM_H
#define COORD_SYSTEM_H

#include <math.h>
#include "num2d.h"
#include "vec2d.h"

//==================================================================================================

class coord_system
{
public:
    num2d center;
    num2d unit;

    explicit coord_system(const num2d &center_, const num2d &unit_):
    center(center_),
    unit(unit_)
    {}

    explicit coord_system(double center_x_ = 0, double center_y_ = 0, double unit_x_ = 20.0, double unit_y_ = 20.0):
    center(num2d(center_x_, center_y_)),
    unit(num2d(unit_x_, unit_y_))
    {}

    ~coord_system()
    {
        center.x = NAN;
        center.y = NAN;
        unit.x   = NAN;
        unit.y   = NAN;
    }

    vec2d get_abs_from_rel(const vec2d &vec) const { return vec2d(vec.x * unit.x, vec.y * unit.y); }
    vec2d get_rel_from_abs(const vec2d &vec) const { return vec2d(vec.x / unit.y, vec.y / unit.y); }
    vec2d get_off_from_rel(const vec2d &vec) const { return vec2d(center) + get_abs_from_rel(vec); }
    vec2d get_rel_from_off(const vec2d &vec) const { return get_rel_from_abs(vec - vec2d(center)); }
};

#endif // COORD_SYSTEM_H
