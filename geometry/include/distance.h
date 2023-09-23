#ifndef DISTANCE_H
#define DISTANCE_H

#include "vec2d.h"
#include "circle.h"
#include "segment.h"

//==================================================================================================

vec2d        distance_segment_circle(const segment_t &segment, const circle_t &circle);
inline vec2d distance_circle_segment(const circle_t &circle, const segment_t &segment);

inline vec2d distance_circle_circle(const circle_t &circle_from, const circle_t &circle_to);

//==================================================================================================

inline vec2d distance_circle_segment(const circle_t &circle, const segment_t &segment)
{
    return -distance_segment_circle(segment, circle);
}

//--------------------------------------------------------------------------------------------------

inline vec2d distance_circle_circle(const circle_t &circle_from, const circle_t &circle_to)
{
    return circle_to.center - circle_from.center;
}

#endif // DISTANCE_H
