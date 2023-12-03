#ifndef VEC2D_H
#define VEC2D_H

#include <math.h>
#include "data_structs/include/algorithm.h"

//==================================================================================================

class vec2d
{
// static
public:
    static vec2d min(const vec2d &op_1, const vec2d &op_2);
    static vec2d max(const vec2d &op_1, const vec2d &op_2);

// member functions
public:
             inline  vec2d();
    explicit inline  vec2d(const double x, const double y);
             inline ~vec2d();

    bool           is_valid         () const;
    void           dump             () const;

    vec2d  inline &floor            ();

    vec2d          get_rotation     (const double degree) const;
    vec2d  inline &rotate           (const double degree);

    double inline  len2             () const;
    double inline  len              () const;

    vec2d  inline  get_normalization(const double new_len = 1) const;
    vec2d  inline &normalize        (const double new_len = 1);

    vec2d  inline  get_normal       () const;
    vec2d  inline &set_normal       ();

    vec2d          get_reflection   (const vec2d &norm) const;
    vec2d  inline &reflect          (const vec2d &norm);

// operators
public:
    vec2d  inline  operator + (const vec2d &add) const;
    vec2d  inline  operator - (const vec2d &sub) const;
    vec2d  inline  operator * (const double mul) const;
    vec2d  inline  operator / (const double div) const;
    vec2d  inline  operator - ()                 const;

    vec2d  inline &operator +=(const vec2d &add);
    vec2d  inline &operator -=(const vec2d &sub);
    vec2d  inline &operator *=(const double mul);
    vec2d  inline &operator /=(const double div);

    double inline  operator , (const vec2d &vec) const;

    bool   inline  operator ==(const vec2d &cmp) const;
    bool   inline  operator !=(const vec2d &cmp) const;

// member data
public:
    double x;
    double y;

// friends
    friend vec2d inline operator *(const double mul, const vec2d &vec);
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

inline vec2d &vec2d::floor()
{
    return (*this) = vec2d(std::floor(x), std::floor(y));
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
