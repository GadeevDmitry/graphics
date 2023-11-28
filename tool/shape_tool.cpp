#include <stdio.h>
#include "shape_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void shape_tool_t::paint_on_press(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color)
{
    (void) perm;

    start  = local_context.position;
    last   = start;

    draw_temp(temp, color);
}

//--------------------------------------------------------------------------------------------------

void shape_tool_t::paint_on_release(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color)
{
    (void) local_context;
    (void) color;

    plugin::Texture *temp_texture = temp->get_texture();
    perm->draw_texture(vec2d(0, 0), vec2d((double) temp_texture->width, (double) temp_texture->height), temp_texture);

    deactivate(perm, temp, local_context, color);
    delete temp_texture;
}

//--------------------------------------------------------------------------------------------------

void shape_tool_t::paint_on_move(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color)
{
    (void) perm;

    last = local_context.position;
    draw_temp(temp, color);
}
