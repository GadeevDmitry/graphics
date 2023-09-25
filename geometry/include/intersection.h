#ifndef INTERSACTION_H
#define INTERSACTION_H

#include "shape_types.h"

//==================================================================================================

inline bool is_intersection_rectangle_point(const rectangle_t &rect, const vec2d &point)
{
    return point.x >= rect.ld_corner.x && point.x <= rect.ru_corner.x &&
           point.y >= rect.ld_corner.y && point.y <= rect.ru_corner.y;
}

#endif // INTERSACTION_H
