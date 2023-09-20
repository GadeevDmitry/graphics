#ifndef MATERIAL_POINT_H
#define MATERIAL_POINT_H

#include "vec2d.h"

//==================================================================================================

struct material_point_t
{
public:
    vec2d position;
    vec2d speed;

    explicit material_point_t(const vec2d &position_ = vec2d(), const vec2d &speed_ = vec2d()):
    position(position_),
    speed(speed_)
    {}

    void refresh(const double time) { position += speed * time; }
};

#endif // MATERIAL_POINT_H
