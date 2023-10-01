#ifndef VEC2D_H
#define VEC2D_H

#include <math.h>
#include "algorithm.h"

//==================================================================================================

class vec2d
{
public:
    double x;
    double y;

    inline          vec2d();
    inline explicit vec2d(const double x_, const double y_);
    inline         ~vec2d();

    inline vec2d  operator + (const vec2d &add) const;
    inline vec2d  operator - (const vec2d &sub) const;
    inline vec2d  operator * (const double mul) const;
    inline vec2d  operator / (const double div) const;
    inline vec2d  operator - ()                 const;

    inline vec2d &operator +=(const vec2d &add);
    inline vec2d &operator -=(const vec2d &sub);
    inline vec2d &operator *=(const double mul);
    inline vec2d &operator /=(const double div);

    inline double operator , (const vec2d &vec) const;

    inline bool   operator ==(const vec2d &cmp) const;
    inline bool   operator !=(const vec2d &cmp) const;

    vec2d         get_rotation(const double degree) const;
    inline vec2d &rotate      (const double degree);

    inline double len2() const;
    inline double len () const;

    inline vec2d  get_normalization(const double new_len = 1) const;
    inline vec2d &normalize        (const double new_len = 1);

    inline vec2d  get_normal() const;
    inline vec2d &set_normal();

    vec2d         get_reflection(const vec2d &norm) const;
    inline vec2d &reflect       (const vec2d &norm);

    friend inline vec2d operator *(const double mul, const vec2d &vec);
};

//--------------------------------------------------------------------------------------------------

inline vec2d::vec2d():
x(0),
y(0)
{}

//--------------------------------------------------------------------------------------------------

inline vec2d::vec2d(const double x_, const double y_):
x(x_),
y(y_)
{}

//--------------------------------------------------------------------------------------------------

inline vec2d::~vec2d()
{
    x = NAN;
    y = NAN;
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::operator +(const vec2d &add) const
{
    return vec2d(x + add.x, y + add.y);
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::operator -(const vec2d &sub) const
{
    return vec2d(x - sub.x, y - sub.y);
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::operator *(const double mul) const
{
    return vec2d(x * mul, y * mul);
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::operator /(const double div) const
{
    return (*this) * (1 / div);
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::operator -() const
{
    return (*this) * (-1);
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::operator +=(const vec2d &add)
{
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::operator -=(const vec2d &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::operator *=(const double mul)
{
    return *this = (*this) * mul;
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::operator /=(const double div)
{
    return *this = (*this) / div;
}

//--------------------------------------------------------------------------------------------------

inline double vec2d::operator ,(const vec2d &vec) const
{
    return x*vec.x + y*vec.y;
}

//--------------------------------------------------------------------------------------------------

inline bool vec2d::operator ==(const vec2d &cmp) const
{
    return dblcmp(x, cmp.x) == 0 && dblcmp(y, cmp.y) == 0;
}

//--------------------------------------------------------------------------------------------------

inline bool vec2d::operator !=(const vec2d &cmp) const
{
    return !((*this) == cmp);
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::rotate(const double degree)
{
    return *this = this->get_rotation(degree);
}

//--------------------------------------------------------------------------------------------------

inline double vec2d::len2() const
{
    return x*x + y*y;
}

//--------------------------------------------------------------------------------------------------

inline double vec2d::len () const
{
    return sqrt(len2());
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::get_normalization(const double new_len) const
{
    return (new_len / len()) * (*this);
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::normalize (const double new_len)
{
    return *this = (*this).get_normalization(new_len);
}

//--------------------------------------------------------------------------------------------------

inline vec2d vec2d::get_normal() const
{
    return vec2d(-y, x);
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::set_normal()
{
    return *this = (*this).get_normal();
}

//--------------------------------------------------------------------------------------------------

inline vec2d &vec2d::reflect(const vec2d &norm)
{
    return *this = (*this).get_reflection(norm);
}

//--------------------------------------------------------------------------------------------------

inline vec2d operator *(const double mul, const vec2d &vec)
{
    return vec * mul;
}

#endif // VEC2D_H
