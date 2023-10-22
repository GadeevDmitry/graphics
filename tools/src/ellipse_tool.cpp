#include <stdio.h>
#include "ellipse_tool.h"
#include "log.h"

//==================================================================================================

void ellipse_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    double x_size  = abs(last.x - start.x);
    double y_size  = abs(last.y - start.y);

    double y_scale = (dblcmp(x_size, 0) == 0) ? 0 : y_size / x_size;
    double x_scale = (dblcmp(y_size, 0) == 0) ? 0 : x_size / y_size;

    temp.clear(color_t::Transparent);

    if (x_size < y_size)
    {
        circle_t circle(vec2d((start.x + last.x) / 2, (start.y + last.y) / 2), x_size / 2);
        temp.draw_circle(circle, color_t::Transparent, color, 1, vec2d(1, y_scale));
    }
    else
    {
        circle_t circle(vec2d((start.x + last.x) / 2, (start.y + last.y) / 2), y_size / 2);
        temp.draw_circle(circle, color_t::Transparent, color, 1, vec2d(x_scale, 1));
    }
}
