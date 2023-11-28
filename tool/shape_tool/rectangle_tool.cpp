#include <stdio.h>
#include "shape_tool/rectangle_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void rectangle_tool_t::draw_temp(RenderTargetI *temp, Color color)
{
    vec2d size(last.x - start.x, last.y - start.y);

    temp->clear();
    temp->draw_rect(start, size, color);
}
