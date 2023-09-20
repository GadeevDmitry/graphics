#ifndef COLOR_H
#define COLOR_H

#include <math.h>

//==================================================================================================

class color_t
{
public:
    double r;
    double g;
    double b;

    explicit color_t(double r_ = 0, double g_ = 0, double b_ = 0):
    r(r_),
    g(g_),
    b(b_)
    {}

    static const color_t White;
    static const color_t Black;
    static const color_t Red;
    static const color_t Green;
    static const color_t Blue;
    static const color_t Orange;

    ~color_t() { r = NAN; g = NAN; b = NAN; }

    color_t operator +(const color_t &add) const { return color_t(r + add.r, g + add.g, b + add.b); }
    color_t operator -(const color_t &sub) const { return color_t(r - sub.r, g - sub.g, b - sub.g); }
    color_t operator *(const color_t &mul) const { return color_t(r * mul.r, g * mul.g, b * mul.b); }
    color_t operator *(const double   mul) const { return color_t(r * mul  , g * mul  , b * mul  ); }

    color_t &operator +=(const color_t &add) { return *this = (*this) + add; }
    color_t &operator -=(const color_t &sub) { return *this = (*this) - sub; }
    color_t &operator *=(const color_t &mul) { return *this = (*this) * mul; }
    color_t &operator *=(const double   mul) { return *this = (*this) * mul; }

    friend color_t operator *(const double mul, const color_t &col) { return col * mul; }
};

#endif // COLOR_H
