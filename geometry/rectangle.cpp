#include <stdio.h>
#include "rectangle.h"
#include "data_structs/include/log.h"

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

//--------------------------------------------------------------------------------------------------

void rectangle_t::dump() const
{
    LOG_TAB_SERVICE_MESSAGE("rectangle_t (address: %p)\n{", "\n", this);
    LOG_TAB++;

    LOG_TAB_MESSAGE("ld_corner = {%15lg, %15lg}\n", ld_corner.x, ld_corner.y);
    LOG_TAB_MESSAGE("ru_corner = {%15lg, %15lg}\n", ru_corner.x, ru_corner.y);

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");
}
