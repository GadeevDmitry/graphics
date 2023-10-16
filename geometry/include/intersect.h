#ifndef INTERSECT_H
#define INTERSECT_H

#include "shape_types.h"

//==================================================================================================

bool is_intersect_rectangle_rectangle(const rectangle_t &rect_1, const rectangle_t &rect_2);
bool    intersect_rectangle_rectangle(      rectangle_t &rect_1, const rectangle_t &rect_2);

bool is_intersect_line_rectangle     (const segment_t   &seg   , const rectangle_t &rect);
bool    intersect_line_rectangle     (      segment_t   &seg   , const rectangle_t &rect);

#endif
