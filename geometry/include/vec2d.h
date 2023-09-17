#ifndef VEC2D_H
#define VEC2D_H

#include <math.h>
#include <algorithm/algorithm.h>

//==================================================================================================

class vec2d
{
public:
    double x;
    double y;

    explicit vec2d(double x_ = 0, double y_ = 0):
    x(x_),
    y(y_)
    {}

    ~vec2d() {x = NAN; y = NAN; }

    vec2d operator +(const vec2d &add) const { return vec2d(x + add.x, y + add.y); }
    vec2d operator -(const vec2d &sub) const { return vec2d(x - sub.x, y - sub.y); }
    vec2d operator *(const double mul) const { return vec2d(x * mul  , y * mul  ); }
    vec2d operator /(const double div) const { return (*this) * (1 / div); }
    vec2d operator -()                 const { return (*this) * (-1); }

    vec2d &operator +=(const vec2d &add) { return *this = (*this) + add; }
    vec2d &operator -=(const vec2d &sub) { return *this = (*this) - sub; }
    vec2d &operator *=(const double mul) { return *this = (*this) * mul; }
    vec2d &operator /=(const double div) { return *this = (*this) / div; }

    friend vec2d operator *(const double mul, const vec2d &vec) { return vec * mul; }

    // Возвращает скалярное произведение двух векторов
    double operator ,(const vec2d &vec) const { return x*vec.x + y*vec.y; }

    bool operator ==(const vec2d &cmp) const { return dblcmp(x, cmp.x) == 0 && dblcmp(y, cmp.y) == 0; }
    bool operator !=(const vec2d &cmp) const { return !((*this) == cmp); }

    vec2d  get_rotation(const double degree) const;
    vec2d &rotate      (const double degree) { return *this = this->get_rotation(degree); }

    double len2() const { return x*x + y*y; }
    double len () const { return sqrt(len2()); }

    vec2d  get_normalization(const double new_len = 1) const { return (new_len / len()) * (*this); }
    vec2d &normalize        (const double new_len = 1) { return *this = (*this).get_normalization(new_len); }

    vec2d  get_normal() const { return vec2d(-y, x); }
    vec2d &set_normal() { return *this = (*this).get_normal(); }
};

#endif // VEC2D_H
