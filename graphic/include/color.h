#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <SFML/Graphics.hpp>

//==================================================================================================

class color_t
{
public:
    double r;
    double g;
    double b;

    static const color_t White;
    static const color_t Black;
    static const color_t Red;
    static const color_t Green;
    static const color_t Blue;
    static const color_t Orange;

    inline          color_t();
    inline explicit color_t(double r_, double g_, double b_);
    inline         ~color_t();

    sf::Color get_sfml_color() const;

    inline color_t  operator + (const color_t &add) const;
    inline color_t  operator - (const color_t &sub) const;
    inline color_t  operator * (const color_t &mul) const;
    inline color_t  operator * (const double   mul) const;

    inline color_t &operator +=(const color_t &add);
    inline color_t &operator -=(const color_t &sub);
    inline color_t &operator *=(const color_t &mul);
    inline color_t &operator *=(const double   mul);

    friend inline color_t operator *(const double mul, const color_t &col);
};

//--------------------------------------------------------------------------------------------------

inline color_t::color_t():
r(0),
g(0),
b(0)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::color_t(double r_, double g_, double b_):
r(r_),
g(g_),
b(b_)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::~color_t()
{
    r = NAN;
    g = NAN;
    b = NAN;
}

//--------------------------------------------------------------------------------------------------

inline color_t color_t::operator +(const color_t &add) const
{
    return color_t(r + add.r, g + add.g, b + add.b);
}

//--------------------------------------------------------------------------------------------------

inline color_t color_t::operator -(const color_t &sub) const
{
    return color_t(r - sub.r, g - sub.g, b - sub.g);
}

//--------------------------------------------------------------------------------------------------

inline color_t color_t::operator *(const color_t &mul) const
{
    return color_t(r * mul.r, g * mul.g, b * mul.b);
}

//--------------------------------------------------------------------------------------------------

inline color_t color_t::operator *(const double mul) const
{
    return color_t(r * mul, g * mul, b * mul);
}

//--------------------------------------------------------------------------------------------------

inline color_t &color_t::operator +=(const color_t &add)
{
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline color_t &color_t::operator -=(const color_t &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline color_t &color_t::operator *=(const color_t &mul)
{
    return *this = (*this) * mul;
}

//--------------------------------------------------------------------------------------------------

inline color_t &color_t::operator *=(const double mul)
{
    return *this = (*this) * mul;
}

//--------------------------------------------------------------------------------------------------

inline color_t operator *(const double mul, const color_t &col)
{
    return col * mul;
}

#endif // COLOR_H
