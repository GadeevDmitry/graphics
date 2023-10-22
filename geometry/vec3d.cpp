#include <stdio.h>
#include "vec3d.h"
#include "data_structs/include/log.h"

//==================================================================================================

bool vec3d::is_valid() const
{
    bool is_valid = true;

    is_valid = (isfinite(x) == 0) ? false : is_valid;
    is_valid = (isfinite(y) == 0) ? false : is_valid;
    is_valid = (isfinite(z) == 0) ? false : is_valid;

    return is_valid;
}

//--------------------------------------------------------------------------------------------------

void vec3d::dump() const
{
    LOG_TAB_SERVICE_MESSAGE("vec3d (address: %p)\n{", "\n", this);
    LOG_TAB++;

    USUAL_FIELD_DUMP("x", "%lg", x);
    USUAL_FIELD_DUMP("y", "%lg", y);
    USUAL_FIELD_DUMP("z", "%lg", z);

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");
}

//--------------------------------------------------------------------------------------------------

vec3d vec3d::get_reflection(const vec3d &norm) const
{
    vec3d norm_ = norm.get_normalization();
    vec3d this_ = get_normalization();
    double len_ = len();

    vec3d reflected = this_ - 2*(norm_, this_)*norm_;
    reflected.normalize(len_);

    return reflected;
}
