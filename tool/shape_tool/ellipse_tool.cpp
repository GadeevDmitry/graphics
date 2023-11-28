#include <stdio.h>
#include "shape_tool/ellipse_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void ellipse_tool_t::draw_temp(RenderTargetI *temp, Color color)
{
    vec2d size(last.x - start.x, last.y - start.y);

    vec2d ld_corner;
    if (size.x > 0)
    {
        if (size.y > 0) ld_corner = start;
        else            ld_corner = vec2d(start.x, last.y);
    }
    else
    {
        if (size.y > 0) ld_corner = vec2d(last.x, start.y);
        else            ld_corner = last;
    }

    temp->clear();
    temp->draw_ellipse(ld_corner, vec2d(abs(size.x), abs(size.y)), color);
}
