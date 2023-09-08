#include <stdio.h>
#include <vec.h>

vec operator ^(const vec &main, double deg)
{
    double rad = M_PI * (deg / 180);

    double cos_ = cos(rad);
    double sin_ = sin(rad);

    return vec(main.x * cos_ - main.y * sin_,
               main.x * sin_ + main.y * cos_);
}

vec &operator ^=(vec &main, double deg)
{
    return main = main ^ deg;
}
