#ifndef INTERSECT_H
#define INTERSECT_H

#include "shape_types.h"

//==================================================================================================

bool is_intersect_rectangle_rectangle(const rectangle_t &rect_1, const rectangle_t &rect_2);
bool    intersect_rectangle_rectangle(      rectangle_t &rect_1, const rectangle_t &rect_2);

#endif
