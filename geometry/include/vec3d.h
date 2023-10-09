#ifndef VEC3D_H
#define VEC3D_H

#include <math.h>
#include "algorithm.h"

//==================================================================================================

class vec3d
{
public:
    double x;
    double y;
    double z;

    inline          vec3d();
    inline explicit vec3d(const double x_, const double y_, const double z_);
    inline         ~vec3d();

    bool is_valid() const;

    inline vec3d  operator + (const vec3d &add) const;
    inline vec3d  operator - (const vec3d &sub) const;
    inline vec3d  operator * (const double mul) const;
    inline vec3d  operator / (const double div) const;
    inline vec3d  operator - ()                 const;

    inline vec3d &operator +=(const vec3d &add);
    inline vec3d &operator -=(const vec3d &sub);
    inline vec3d &operator *=(const double mul);
    inline vec3d &operator /=(const double div);

    inline double operator , (const vec3d &vec) const;

    inline bool   operator ==(const vec3d &cmp) const;
    inline bool   operator !=(const vec3d &cmp) const;

    inline double len2() const;
    inline double len () const;

    inline vec3d  get_normalization(const double new_len = 1) const;
    inline vec3d &normalize        (const double new_len = 1);

    vec3d         get_reflection   (const vec3d &norm) const;
    vec3d        &reflect          (const vec3d &norm) const;

    friend inline vec3d operator *(const double mul, const vec3d &vec);
};

//--------------------------------------------------------------------------------------------------

inline vec3d::vec3d():
x(0),
y(0),
z(0)
{}

//--------------------------------------------------------------------------------------------------

inline vec3d::vec3d(const double x_, const double y_, const double z_):
x(x_),
y(y_),
z(z_)
{}

//--------------------------------------------------------------------------------------------------

inline vec3d::~vec3d()
{
    x = NAN;
    y = NAN;
    z = NAN;
}

//--------------------------------------------------------------------------------------------------

inline vec3d vec3d::operator +(const vec3d &add) const
{
    return vec3d(x + add.x, y + add.y, z + add.z);
}

//--------------------------------------------------------------------------------------------------

inline vec3d vec3d::operator -(const vec3d &sub) const
{
    return vec3d(x - sub.x, y - sub.y, z - sub.z);
}

//--------------------------------------------------------------------------------------------------

inline vec3d vec3d::operator *(const double mul) const
{
    return vec3d(x * mul, y * mul, z * mul);
}

//--------------------------------------------------------------------------------------------------

inline vec3d vec3d::operator /(const double div) const
{
    return (*this) * (1 / div);
}

//--------------------------------------------------------------------------------------------------

inline vec3d vec3d::operator -() const
{
    return (*this) * (-1);
}

//--------------------------------------------------------------------------------------------------

inline vec3d &vec3d::operator +=(const vec3d &add)
{ 
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline vec3d &vec3d::operator -=(const vec3d &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline vec3d &vec3d::operator *=(const double mul)
{
    return *this = (*this) * mul;
}

//--------------------------------------------------------------------------------------------------

inline vec3d &vec3d::operator /=(const double div)
{
    return *this = (*this) / div;
}

//--------------------------------------------------------------------------------------------------

inline double vec3d::operator ,(const vec3d &vec) const
{
    return x*vec.x + y*vec.y + z*vec.z;
}

//--------------------------------------------------------------------------------------------------

inline bool vec3d::operator ==(const vec3d &cmp) const
{
    return dblcmp(x, cmp.x) == 0 && dblcmp(y, cmp.y) == 0 && dblcmp(z, cmp.z) == 0;
}

//--------------------------------------------------------------------------------------------------

inline bool vec3d::operator !=(const vec3d &cmp) const
{
    return !((*this) == cmp);
}

//--------------------------------------------------------------------------------------------------

inline double vec3d::len2() const
{
    return x*x + y*y + z*z;
}

//--------------------------------------------------------------------------------------------------

inline double vec3d::len () const
{
    return sqrt(len2());
}

//--------------------------------------------------------------------------------------------------

inline vec3d vec3d::get_normalization(const double new_len) const
{
    return (new_len / len()) * (*this);
}

//--------------------------------------------------------------------------------------------------

inline vec3d &vec3d::normalize(const double new_len)
{
    return *this = (*this).get_normalization(new_len);
}

//--------------------------------------------------------------------------------------------------

inline vec3d operator *(const double mul, const vec3d &vec)
{
    return vec * mul;
}

#endif // VEC3D_H
