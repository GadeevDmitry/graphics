#include <stdio.h>
#include <vec2d.h>

//==================================================================================================

vec2d  vec2d::get_rotation(const double degree) const
{
    double rad = M_PI * (degree / 180);

    double cos_ = cos(rad);
    double sin_ = sin(rad);

    return vec2d(x * cos_ - y * sin_,
                 x * sin_ + y * cos_);
}
