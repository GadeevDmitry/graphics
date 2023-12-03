#include <stdio.h>
#include "window/canvas_window.h"

//==================================================================================================

canvas_window_t::canvas_window_t(tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color_, const char *wnd_name):
window_t         (color_, wnd_name),
canvas_controller(tool_manager, filter_manager),
canvas           (new canvas_t(canvas_controller))
{
    register_subwidget(widget_proxy_t(canvas));
}

//--------------------------------------------------------------------------------------------------

canvas_window_t::canvas_window_t(const rectangle_t &enclosing_, tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color_, const char *wnd_name):
window_t         (color_, wnd_name),
canvas_controller(tool_manager, filter_manager),
canvas           (new canvas_t(canvas_controller))
{
    register_subwidget(widget_proxy_t(canvas));
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void canvas_window_t::create_canvas()
{
    const vec2d canvas_off(20, 20);
    const vec2d wnd_size = enclosing.get_size();

    if ((wnd_size.y < header_menu_height + 2 * canvas_off.y) ||
        (wnd_size.x <                      2 * canvas_off.x))
    {
        LOG_ERROR("CAN'T CREATE WINDOW: size is too small for canvas\n");
        return;
    }

    canvas->create(rectangle_t(
        enclosing.ld_corner + vec2d(0, header_menu_height) + canvas_off,
        enclosing.ru_corner                                - canvas_off));
}
