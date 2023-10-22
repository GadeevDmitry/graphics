#ifndef VEC3D_H
#define VEC3D_H

#include <math.h>
#include "data_structs/include/algorithm.h"

//==================================================================================================

class vec3d
{
// member functions
public:
             inline  vec3d();
    explicit inline  vec3d(const double x, const double y, const double z);
             inline ~vec3d();

    bool           is_valid         () const;
    void           dump             () const;

    double inline  len2             () const;
    double inline  len              () const;

    vec3d  inline  get_normalization(const double new_len = 1) const;
    vec3d  inline &normalize        (const double new_len = 1);

    vec3d          get_reflection   (const vec3d &norm) const;
    vec3d         &reflect          (const vec3d &norm) const;

// operators
public:
    vec3d  inline  operator + (const vec3d &add) const;
    vec3d  inline  operator - (const vec3d &sub) const;
    vec3d  inline  operator * (const double mul) const;
    vec3d  inline  operator / (const double div) const;
    vec3d  inline  operator - ()                 const;

    vec3d  inline &operator +=(const vec3d &add);
    vec3d  inline &operator -=(const vec3d &sub);
    vec3d  inline &operator *=(const double mul);
    vec3d  inline &operator /=(const double div);

    double inline  operator , (const vec3d &vec) const;

    bool   inline  operator ==(const vec3d &cmp) const;
    bool   inline  operator !=(const vec3d &cmp) const;

// member data
public:
    double x;
    double y;
    double z;

// friends
    friend vec3d inline operator *(const double mul, const vec3d &vec);
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
