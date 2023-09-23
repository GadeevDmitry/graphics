#ifndef SEGMENT_H
#define SEGMENT_H

#include "vec2d.h"

//==================================================================================================

class segment_t
{
public:
    vec2d endpoint_1;
    vec2d endpoint_2;

    explicit segment_t(const vec2d &endpoint_1_ = vec2d(), const vec2d &endpoint_2_ = vec2d()):
    endpoint_1(endpoint_1_),
    endpoint_2(endpoint_2_)
    {}

    ~segment_t() {}

    segment_t operator +(const vec2d &add) const { return segment_t(endpoint_1 + add, endpoint_2 + add); }
    segment_t operator -(const vec2d &sub) const { return segment_t(endpoint_1 - sub, endpoint_2 - sub); }

    segment_t &operator +=(const vec2d &add) { return *this = (*this) + add; }
    segment_t &operator -=(const vec2d &sub) { return *this = (*this) - sub; }

    vec2d get_normal() const { return (endpoint_2 - endpoint_1).get_normal(); }
};

#endif // SEGMENT_H
