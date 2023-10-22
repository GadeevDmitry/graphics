#ifndef CIRCLE_H
#define CIRCLE_H

#include "vec2d.h"

//==================================================================================================

class circle_t
{
// member functions
public:
             inline  circle_t();
    explicit inline  circle_t(const vec2d &center, const double radius);
             inline ~circle_t();

// operators
public:
    circle_t inline  operator + (const vec2d &add) const;
    circle_t inline  operator - (const vec2d &sub) const;
    circle_t inline  operator * (const double mul) const;
    circle_t inline  operator / (const double div) const;

    circle_t inline &operator +=(const vec2d &add);
    circle_t inline &operator -=(const vec2d &sub);
    circle_t inline &operator *=(const double mul);
    circle_t inline &operator /=(const double div);

// member data
public:
    vec2d  center;
    double radius;

// friends
    friend circle_t inline operator *(const double mul, const circle_t &circle);
};

//--------------------------------------------------------------------------------------------------

inline circle_t::circle_t():
center(),
radius(0)
{}

//--------------------------------------------------------------------------------------------------

inline circle_t::circle_t(const vec2d &center_, const double radius_):
center(center_),
radius(radius_)
{}

//--------------------------------------------------------------------------------------------------

inline circle_t::~circle_t()
{
    radius = NAN;
}

//--------------------------------------------------------------------------------------------------

inline circle_t circle_t::operator +(const vec2d &add) const
{
    return circle_t(center + add, radius);
}

//--------------------------------------------------------------------------------------------------

inline circle_t circle_t::operator -(const vec2d &sub) const
{
    return circle_t(center - sub, radius);
}

//--------------------------------------------------------------------------------------------------

inline circle_t circle_t::operator *(const double mul) const
{
    return circle_t(center, radius * mul);
}

//--------------------------------------------------------------------------------------------------

inline circle_t circle_t::operator /(const double div) const
{
    return circle_t(center, radius / div);
}

//--------------------------------------------------------------------------------------------------

inline circle_t &circle_t::operator +=(const vec2d &add)
{
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline circle_t &circle_t::operator -=(const vec2d &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline circle_t &circle_t::operator *=(const double mul)
{
    return *this = (*this) * mul;
}

//--------------------------------------------------------------------------------------------------

inline circle_t &circle_t::operator /=(const double div)
{
    return *this = (*this) / div;
}

//--------------------------------------------------------------------------------------------------

inline circle_t operator *(const double mul, const circle_t &circle)
{
    return circle * mul;
}

#endif // CIRCLE_H
