#ifndef VEC3D_H
#define VEC3D_H

#include <math.h>
#include <algorithm/algorithm.h>

//==================================================================================================

class vec3d
{
public:
    double x;
    double y;
    double z;

    explicit vec3d(double x_ = 0, double y_ = 0, double z_ = 0):
    x(x_),
    y(y_),
    z(z_)
    {}

    ~vec3d() {x = NAN; y = NAN; z = NAN; }

    vec3d operator +(const vec3d &add) const { return vec3d(x + add.x, y + add.y, z + add.z); }
    vec3d operator -(const vec3d &sub) const { return vec3d(x - sub.x, y - sub.y, z - sub.z); }
    vec3d operator *(const double mul) const { return vec3d(x * mul  , y * mul  , z * mul  ); }
    vec3d operator /(const double div) const { return (*this) * (1 / div); }
    vec3d operator -()                 const { return (*this) * (-1); }

    vec3d &operator +=(const vec3d &add) { return *this = (*this) + add; }
    vec3d &operator -=(const vec3d &sub) { return *this = (*this) - sub; }
    vec3d &operator *=(const double mul) { return *this = (*this) * mul; }
    vec3d &operator /=(const double div) { return *this = (*this) / div; }

    friend vec3d operator *(const double mul, const vec3d &vec) { return vec * mul; }

    // Возвращает скалярное произведение двух векторов
    double operator ,(const vec3d &vec) const { return x*vec.x + y*vec.y + z*vec.z; }

    bool operator ==(const vec3d &cmp) const { return dblcmp(x, cmp.x) == 0 &&
                                                      dblcmp(y, cmp.y) == 0 &&
                                                      dblcmp(z, cmp.z) == 0; }
    bool operator !=(const vec3d &cmp) const { return !((*this) == cmp); }

    double len2() const { return x*x + y*y + z*z; }
    double len () const { return sqrt(len2()); }

    vec3d  get_normalization(const double new_len = 1) const { return (new_len / len()) * (*this); }
    vec3d &normalize        (const double new_len = 1) { return *this = (*this).get_normalization(new_len); }

    vec3d  get_reflection(const vec3d &norm) const;
    vec3d &reflect       (const vec3d &norm) const;
};

#endif // VEC3D_H
