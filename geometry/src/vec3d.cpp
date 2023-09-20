#include <stdio.h>
#include "vec3d.h"

//==================================================================================================

vec3d vec3d::get_reflection(const vec3d &norm) const
{
    vec3d norm_ = norm.get_normalization();
    vec3d this_ = get_normalization();
    double len_ = len();

    vec3d reflected = this_ - 2*(norm_, this_)*norm_;
    reflected.normalize(len_);

    return reflected;
}
