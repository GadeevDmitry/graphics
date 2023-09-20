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
};

#endif // SEGMENT_H
