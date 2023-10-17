#include <stdio.h>
#include "widget.h"
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

//--------------------------------------------------------------------------------------------------

void shape_tool_t::draw_temp(render_texture_t &temp, const color_t &color)
{
    double x_size = abs(last.x - start.x);
    double y_size = abs(last.y - start.y);
    double scale  = (dblcmp(x_size, 0) == 0) ? 0 : y_size / x_size;

    circle_t circle(vec2d((start.x + last.x) / 2, (start.y + last.y) / 2), x_size / 2);

    temp.clear(color_t(0, 0, 0, 0));
    temp.draw_filled_circle(circle, color, color_t(0, 0, 0, 0), vec2d(1, scale));
}
