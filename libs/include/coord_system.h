#ifndef COORD_SYSTEM_H
#define COORD_SYSTEM_H

#include <math.h>
#include <vec.h>

//==================================================================================================

class coord_system
{
public:
    double x_0;
    double y_0;

    double x_1_len;
    double y_1_len;

    coord_system(double x_0_, double y_0_, double x_1_len_ = 20.0, double y_1_len_ = 20.0):
    x_0(x_0_),
    y_0(y_0_),
    x_1_len(x_1_len_),
    y_1_len(y_1_len_)
    {}

    ~coord_system()
    {
        x_0 = NAN;
        y_0 = NAN;
        x_1_len = NAN;
        y_1_len = NAN;
    }

    inline vec get_vec_from_pixel(vec pix) const;
    inline vec get_pixel_from_vec(vec v) const;

};

//==================================================================================================

inline vec coord_system::get_vec_from_pixel(vec pix) const
{
    return vec((pix.x - x_0) / x_1_len, (pix.y - y_0) / y_1_len);
}

inline vec coord_system::get_pixel_from_vec(vec v) const
{
    return vec(x_1_len * v.x, y_1_len * v.y);
}

#endif // COORD_SYSTEM_H
