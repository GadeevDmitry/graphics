#include <stdio.h>
#include "shape_tool.h"
#include "log.h"

//==================================================================================================

void shape_tool_t::paint_on_mouse_press(render_texture_t &perm, render_texture_t &temp, const color_t &color,
                                        const vec2d &texture_off, const MOUSE_BUTTON_TYPE &btn)
{
    (void) btn;
    (void) perm;

    start  = widget_t::get_mouse_context().pos;
    start -= texture_off;
    last   = start;

    draw_temp(temp, color);
}

//--------------------------------------------------------------------------------------------------

void shape_tool_t::paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const color_t &color,
                                          const vec2d &texture_off, const MOUSE_BUTTON_TYPE &btn)
{
    (void) btn;
    (void) color;
    (void) texture_off;

    texture_t temp_texture = temp.get_texture();
    perm.draw_texture(temp_texture, vec2d(0, 0), temp_texture.get_size());
}

//--------------------------------------------------------------------------------------------------

void shape_tool_t::paint_on_mouse_move(render_texture_t &perm, render_texture_t &temp, const color_t &color,
                                       const vec2d &texture_off, const vec2d &off)
{
    (void) perm;
    (void) texture_off;

    last += off;
    draw_temp(temp, color);
}
