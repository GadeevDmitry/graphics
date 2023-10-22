#include <stdio.h>
#include "shape_tool/line_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void line_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    temp.clear(color_t::Transparent);
    temp.draw_line(segment_t(start, last), color);
}
