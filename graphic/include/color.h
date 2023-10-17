#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <SFML/Graphics.hpp>

//==================================================================================================

class color_t
{
///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
public:
    static const color_t White;
    static const color_t Black;
    static const color_t Red;
    static const color_t Green;
    static const color_t Blue;
    static const color_t Orange;

    static color_t get_rand_color();

///////////////////////////////////////////////
// FRIENDS
///////////////////////////////////////////////
public:
    friend inline color_t operator *(const double mul, const color_t &col);

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    double r;
    double g;
    double b;
    double a;

    inline          color_t();
    inline explicit color_t(double r_, double g_, double b_, double a_ = 1.0);
    inline         ~color_t();

    sf::Color get_sfml_color() const;
    void maximize_brightness();

    inline color_t  operator + (const color_t &add) const;
    inline color_t  operator - (const color_t &sub) const;
    inline color_t  operator * (const color_t &mul) const;
    inline color_t  operator * (const double   mul) const;

    inline color_t &operator +=(const color_t &add);
    inline color_t &operator -=(const color_t &sub);
    inline color_t &operator *=(const color_t &mul);
    inline color_t &operator *=(const double   mul);
};

//--------------------------------------------------------------------------------------------------

inline color_t::color_t():
r(0),
g(0),
b(0)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::color_t(double r_, double g_, double b_, double a_):
r(r_),
g(g_),
b(b_),
a(a_)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::~color_t()
{
    r = NAN;
    g = NAN;
    b = NAN;
    a = NAN;
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
