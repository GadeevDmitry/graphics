#include <stdio.h>
#include "rectangle.h"
#include "log.h"

//==================================================================================================

void rectangle_t::dump(const void *rect_)
{
    const rectangle_t *rect = (const rectangle_t *) rect_;

    LOG_TAB_SERVICE_MESSAGE("rectangle_t (address: %p)\n{", "\n", rect);
    LOG_TAB++;

    LOG_TAB_MESSAGE("ld_corner = {%15lg, %15lg}\n", rect->ld_corner.x, rect->ld_corner.y);
    LOG_TAB_MESSAGE("ru_corner = {%15lg, %15lg}\n", rect->ru_corner.x, rect->ru_corner.y);

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");
}

//--------------------------------------------------------------------------------------------------

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
