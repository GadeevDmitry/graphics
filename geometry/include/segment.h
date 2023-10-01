#ifndef SEGMENT_H
#define SEGMENT_H

#include "vec2d.h"

//==================================================================================================

class segment_t
{
public:
    vec2d endpoint_1;
    vec2d endpoint_2;

    inline          segment_t();
    inline explicit segment_t(const vec2d &endpoint_1_, const vec2d &endpoint_2_);
    inline explicit segment_t(const vec2d &endpoint_1_, const double width_, const double height_);
    inline         ~segment_t() {}

    inline segment_t  operator + (const vec2d &add) const;
    inline segment_t  operator - (const vec2d &sub) const;

    inline segment_t &operator +=(const vec2d &add);
    inline segment_t &operator -=(const vec2d &sub);

    inline vec2d get_normal() const;
};

//--------------------------------------------------------------------------------------------------

inline segment_t::segment_t():
endpoint_1(),
endpoint_2()
{}

//--------------------------------------------------------------------------------------------------

inline segment_t::segment_t(const vec2d &endpoint_1_, const vec2d &endpoint_2_):
endpoint_1(endpoint_1_),
endpoint_2(endpoint_2_)
{}

//--------------------------------------------------------------------------------------------------

inline  segment_t::segment_t(const vec2d &endpoint_1_, const double width_, const double height_):
endpoint_1(endpoint_1_),
endpoint_2(endpoint_1_ + vec2d(width_, height_))
{}

//--------------------------------------------------------------------------------------------------

inline segment_t segment_t::operator +(const vec2d &add) const
{
    return segment_t(endpoint_1 + add, endpoint_2 + add);
}

//--------------------------------------------------------------------------------------------------

inline segment_t segment_t::operator -(const vec2d &sub) const
{
    return segment_t(endpoint_1 - sub, endpoint_2 - sub);
}

//--------------------------------------------------------------------------------------------------

inline segment_t &segment_t::operator +=(const vec2d &add)
{
    return *this = (*this) + add;
}

//--------------------------------------------------------------------------------------------------

inline segment_t &segment_t::operator -=(const vec2d &sub)
{
    return *this = (*this) - sub;
}

//--------------------------------------------------------------------------------------------------

inline vec2d segment_t::get_normal() const
{
    return (endpoint_2 - endpoint_1).get_normal();
}

#endif // SEGMENT_H
