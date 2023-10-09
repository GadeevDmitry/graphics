#include <stdio.h>
#include "rectangle.h"

//==================================================================================================

bool rectangle_t::is_valid() const
{
    bool is_valid = true;

    is_valid = ld_corner.is_valid() ? is_valid : false;
    is_valid = ru_corner.is_valid() ? is_valid : false;

    if (!is_valid) return false;

    is_valid = (ld_corner.x < ru_corner.x) ? is_valid : false;
    is_valid = (ld_corner.y < ru_corner.y) ? is_valid : false;

    return is_valid;
}
