#include <stdio.h>
#include <stdlib.h>

#include "distance.h"

//==================================================================================================

vec2d distance_segment_circle(const segment_t &segment, const circle_t &circle)
{
    vec2d seg    = segment.endpoint_2 - segment.endpoint_1;
    vec2d circ_1 = circle.center      - segment.endpoint_1;
    vec2d circ_2 = circle.center      - segment.endpoint_2;

    double mul_1 = (seg, circ_1);
    double mul_2 = (seg, circ_2);

    if ((mul_1 <= 0 && mul_2 <= 0) ||
        (mul_1 >= 0 && mul_2 >= 0))
    {
        return (circ_1.len2() < circ_2.len2()) ? circ_1 : circ_2;
    }

    vec2d projection = (mul_1 / seg.len2()) * seg;
    return circ_1 - projection;
}
