#include <stdio.h>
#include "shape_tool/line_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void line_tool_t::draw_temp(RenderTargetI *temp, Color color)
{
    temp->clear();
    temp->draw_line(start, last, color);
}
