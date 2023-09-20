#ifndef PISTON_H
#define PISTON_H

#include "draw.h"
#include "color.h"
#include "segment.h"
#include "material_point.h"

//==================================================================================================

class piston_t
{
public:
    material_point_t center;
    segment_t        shape ;

    explicit piston_t(const material_point_t &center_, const segment_t &shape_):
    center(center_),
    shape(shape_)
    {}

    void draw(sf::RenderWindow &wnd, const sf::Color &col) const
    {
        return draw_segment(shape, wnd, col);
    }
};

#endif // PISTON_H
