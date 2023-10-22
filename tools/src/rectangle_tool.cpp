#include <stdio.h>
#include "widget.h"
#include "rectangle_tool.h"
#include "log.h"

//==================================================================================================

void rectangle_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    temp.clear(color_t(0, 0, 0, 0));
    temp.draw_rectangle(rectangle_t(start, last), color_t::Transparent, color, 4);
}
