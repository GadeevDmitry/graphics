#include <stdio.h>
#include "shape_tool.h"
#include "data_structs/include/log.h"

//==================================================================================================

void shape_tool_t::paint_on_mouse_press(render_texture_t &perm, render_texture_t &temp, const color_t &color,
                                        const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) btn;
    (void) perm;

    start  = local_context.pos;
    last   = start;

    draw_temp(temp, color);
}

//--------------------------------------------------------------------------------------------------

void shape_tool_t::paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const color_t &color,
                                          const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) btn;
    (void) color;
    (void) local_context;

    texture_t temp_texture = temp.get_texture();
    perm.draw_texture(temp_texture, vec2d(0, 0), temp_texture.get_size());
}

//--------------------------------------------------------------------------------------------------

void shape_tool_t::paint_on_mouse_move(render_texture_t &perm, render_texture_t &temp, const color_t &color,
                                       const eventable::mouse_context_t &local_context, const vec2d &off)
{
    (void) perm;
    (void) local_context;

    last += off;
    draw_temp(temp, color);
}
