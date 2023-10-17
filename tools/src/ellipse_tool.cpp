#include <stdio.h>
#include "widget.h"
#include "ellipse_tool.h"
#include "log.h"

//==================================================================================================

void ellipse_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    double x_size = abs(last.x - start.x);
    double y_size = abs(last.y - start.y);
    double scale  = (dblcmp(x_size, 0) == 0) ? 0 : y_size / x_size;

    circle_t circle(vec2d((start.x + last.x) / 2, (start.y + last.y) / 2), x_size / 2);

    temp.clear(color_t(0, 0, 0, 0));
    temp.draw_filled_circle(circle, color, color_t(0, 0, 0, 0), vec2d(1, scale));
}
