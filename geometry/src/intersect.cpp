#include <stdio.h>
#include "intersect.h"

//==================================================================================================

static rectangle_t get_intersect_rectangle_rectangle(const rectangle_t &rect_1,
                                                     const rectangle_t &rect_2);

//==================================================================================================

static rectangle_t get_intersect_rectangle_rectangle(const rectangle_t &rect_1,
                                                     const rectangle_t &rect_2)
{
    return rectangle_t(vec2d::max(rect_1.ld_corner, rect_2.ld_corner),
                       vec2d::min(rect_1.ru_corner, rect_2.ru_corner));
}

//--------------------------------------------------------------------------------------------------

bool is_intersect_rectangle_rectangle(const rectangle_t &rect_1,
                                      const rectangle_t &rect_2)
{
    rectangle_t intersect = get_intersect_rectangle_rectangle(rect_1, rect_2);
    return      intersect.is_valid();
}

//--------------------------------------------------------------------------------------------------

bool intersect_rectangle_rectangle(      rectangle_t &rect_1,
                                   const rectangle_t &rect_2)
{
    rectangle_t intersect = get_intersect_rectangle_rectangle(rect_1, rect_2);
    if (!intersect.is_valid()) return false;

    rect_1 = intersect;
    return true;
}
