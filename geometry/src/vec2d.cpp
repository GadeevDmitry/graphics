#include <iostream>
#include <stdio.h>
#include "vec2d.h"
#include "log.h"

//==================================================================================================

void vec2d::dump(const void *vec_)
{
    const vec2d *vec = (const vec2d *) vec_;

    LOG_TAB_SERVICE_MESSAGE("vec2d (address: %p)\n{", "\n", vec);
    LOG_TAB++;

    USUAL_FIELD_DUMP("x", "%lg", vec->x);
    USUAL_FIELD_DUMP("y", "%lg", vec->y);

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");
}

//--------------------------------------------------------------------------------------------------

bool vec2d::is_valid() const
{
    bool is_valid = true;

    is_valid = (isfinite(x) == 0) ? false : is_valid;
    is_valid = (isfinite(y) == 0) ? false : is_valid;

    return is_valid;
}

//--------------------------------------------------------------------------------------------------

vec2d vec2d::get_rotation(const double degree) const
{
    double rad = M_PI * (degree / 180);

    double cos_ = cos(rad);
    double sin_ = sin(rad);

    return vec2d(x * cos_ - y * sin_,
                 x * sin_ + y * cos_);
}

//--------------------------------------------------------------------------------------------------

vec2d vec2d::get_reflection(const vec2d &norm) const
{
    vec2d norm_ = norm.get_normalization();
    vec2d this_ = get_normalization();
    double len_ = len();

    if ((norm_, this_) > 0) norm_ = -norm_;

    vec2d reflected = this_ - 2*(norm_, this_)*norm_;
    reflected.normalize(len_);

    return reflected;
}

//--------------------------------------------------------------------------------------------------

vec2d vec2d::min(const vec2d &op_1, const vec2d &op_2)
{
    return vec2d(std::min(op_1.x, op_2.x),
                 std::min(op_1.y, op_2.y));
}

//--------------------------------------------------------------------------------------------------

vec2d vec2d::max(const vec2d &op_1, const vec2d &op_2)
{
    return vec2d(std::max(op_1.x, op_2.x),
                 std::max(op_1.y, op_2.y));
}
