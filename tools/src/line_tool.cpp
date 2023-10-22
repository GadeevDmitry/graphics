#include <stdio.h>
#include "line_tool.h"
#include "log.h"

//==================================================================================================

void line_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    temp.clear(color_t::Transparent);
    temp.draw_line(segment_t(start, last), color);
}
