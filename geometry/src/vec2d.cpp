#include <stdio.h>
#include "vec2d.h"

//==================================================================================================

vec2d vec2d::get_rotation(const double degree) const
{
    double rad = M_PI * (degree / 180);

    double cos_ = cos(rad);
    double sin_ = sin(rad);

    return vec2d(x * cos_ - y * sin_,
                 x * sin_ + y * cos_);
}

vec2d vec2d::get_reflection(const vec2d &norm) const
{
    vec2d norm_ = norm.get_normalization();
    vec2d this_ = get_normalization();
    double len_ = len();

    vec2d reflected = this_ - 2*(norm_, this_)*norm_;
    reflected.normalize(len_);

    return reflected;
}
