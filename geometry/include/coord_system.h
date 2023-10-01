#ifndef COORD_SYSTEM_H
#define COORD_SYSTEM_H

#include "vec2d.h"

//==================================================================================================

class coord_system
{
public:
    vec2d center;
    vec2d unit;

    inline          coord_system();
    inline explicit coord_system(const vec2d &center_, const vec2d &unit_);
    inline         ~coord_system() {}

    inline coord_system  operator + (const vec2d &add) const;
    inline coord_system  operator - (const vec2d &sub) const;
    inline coord_system  operator * (const double mul) const;
    inline coord_system  operator / (const double div) const;

    inline coord_system &operator +=(const vec2d &add);
    inline coord_system &operator -=(const vec2d &sub);
    inline coord_system &operator *=(const double mul);
    inline coord_system &operator /=(const double div);

    inline vec2d get_abs_from_rel(const vec2d &vec) const;
    inline vec2d get_rel_from_abs(const vec2d &vec) const;
    inline vec2d get_off_from_rel(const vec2d &vec) const;
    inline vec2d get_rel_from_off(const vec2d &vec) const;

    friend inline coord_system operator *(const double mul, const coord_system &sys);
};

//--------------------------------------------------------------------------------------------------

inline coord_system::coord_system():
center(),
unit  ()
{}

//--------------------------------------------------------------------------------------------------

inline coord_system::coord_system(const vec2d &center_, const vec2d &unit_):
center(center_),
unit  (unit_)
{}

//--------------------------------------------------------------------------------------------------

inline coord_system coord_system::operator +(const vec2d &add) const
{
    return coord_system(center + add, unit);
}

//--------------------------------------------------------------------------------------------------

inline coord_system coord_system::operator -(const vec2d &sub) const
{
    return coord_system(center - sub, unit);
}

//--------------------------------------------------------------------------------------------------

inline coord_system coord_system::operator *(const double mul) const
{
    return coord_system(center, unit * mul);
}

//--------------------------------------------------------------------------------------------------

inline coord_system coord_system::operator /(const double div) const
{
    return coord_system(center, unit / div);
}

//--------------------------------------------------------------------------------------------------

inline coord_system &coord_system::operator +=(const vec2d &add)
{
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline coord_system &coord_system::operator -=(const vec2d &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline coord_system &coord_system::operator *=(const double mul)
{
    return *this = (*this) * mul;
}

//--------------------------------------------------------------------------------------------------

inline coord_system &coord_system::operator /=(const double div)
{
    return *this = (*this) / div;
}

//--------------------------------------------------------------------------------------------------

inline coord_system operator *(const double mul, const coord_system &sys)
{
    return sys * mul;
}

//--------------------------------------------------------------------------------------------------

inline vec2d coord_system::get_abs_from_rel(const vec2d &vec) const
{
    return vec2d(vec.x * unit.x, vec.y * unit.y);
}

//--------------------------------------------------------------------------------------------------

inline vec2d coord_system::get_rel_from_abs(const vec2d &vec) const
{
    return vec2d(vec.x / unit.x, vec.y / unit.y);
}

//--------------------------------------------------------------------------------------------------

inline vec2d coord_system::get_off_from_rel(const vec2d &vec) const
{
    return vec2d(center) + get_abs_from_rel(vec);
}

//--------------------------------------------------------------------------------------------------

inline vec2d coord_system::get_rel_from_off(const vec2d &vec) const
{
    return get_rel_from_abs(vec - vec2d(center));
}

#endif // COORD_SYSTEM_H
