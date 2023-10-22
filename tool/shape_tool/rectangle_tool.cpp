#include <stdio.h>
#include "shape_tool/rectangle_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void rectangle_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    temp.clear(color_t::Transparent);
    temp.draw_rectangle(rectangle_t(start, last), color_t::Transparent, color, 1);
}
