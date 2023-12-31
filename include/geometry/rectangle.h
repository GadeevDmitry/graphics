#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vec2d.h"

//==================================================================================================

class rectangle_t
{
// member functions
public:
             inline  rectangle_t();
    explicit inline  rectangle_t(const vec2d &ld_corner, const vec2d &ru_corner);
    explicit inline  rectangle_t(const vec2d &ld_corner, const double width, const double height);
             inline ~rectangle_t() {}

    bool         is_valid       () const;
    void         dump           () const;

    vec2d inline lu_corner      () const;
    vec2d inline rd_corner      () const;

    bool  inline is_point_inside(const vec2d &pos) const;
    vec2d inline get_size       () const;

// operators
public:
    rectangle_t inline  operator + (const vec2d &add) const;
    rectangle_t inline  operator - (const vec2d &sub) const;

    rectangle_t inline &operator +=(const vec2d &add);
    rectangle_t inline &operator -=(const vec2d &sub);

// member data
public:
    vec2d ld_corner;
    vec2d ru_corner;
};

//--------------------------------------------------------------------------------------------------

inline rectangle_t::rectangle_t():
ld_corner(),
ru_corner()
{}

//--------------------------------------------------------------------------------------------------

inline rectangle_t::rectangle_t(const vec2d &ld_corner_, const vec2d &ru_corner_):
ld_corner(ld_corner_),
ru_corner(ru_corner_)
{}

//--------------------------------------------------------------------------------------------------

inline rectangle_t::rectangle_t(const vec2d &ld_corner_, const double width_, const double height_):
ld_corner(ld_corner_),
ru_corner(ld_corner_ + vec2d(width_, height_))
{}

//--------------------------------------------------------------------------------------------------

inline rectangle_t rectangle_t::operator +(const vec2d &add) const
{
    return rectangle_t(ld_corner + add, ru_corner + add);
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t rectangle_t::operator -(const vec2d &sub) const
{
    return rectangle_t(ld_corner - sub, ru_corner - sub);
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t &rectangle_t::operator +=(const vec2d &add)
{
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t &rectangle_t::operator -=(const vec2d &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline vec2d rectangle_t::lu_corner() const
{
    return vec2d(ld_corner.x, ru_corner.y);
}

//--------------------------------------------------------------------------------------------------

inline vec2d rectangle_t::rd_corner() const
{
    return vec2d(ru_corner.x, ld_corner.y);
}

//--------------------------------------------------------------------------------------------------

inline bool rectangle_t::is_point_inside(const vec2d &pos) const
{
    return (ld_corner.x <= pos.x) && (ru_corner.x >= pos.x) &&
           (ld_corner.y <= pos.y) && (ru_corner.y >= pos.y);
}

//--------------------------------------------------------------------------------------------------

inline vec2d rectangle_t::get_size() const
{
    return ru_corner - ld_corner;
}

#endif // RECTANGLE_H
