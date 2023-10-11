#include <stdio.h>
#include "window.h"
#include "log.h"

//==================================================================================================

bool move_window(void *window_, const widget_t::mouse_context_t &context);

//--------------------------------------------------------------------------------------------------

static const double HEADER_MENU_HEIGHT = 30;

//==================================================================================================

window_t::window_t(const rectangle_t &region_):
widget_manager_t(nullptr, region_),
region          (region_),
header_menu     (nullptr)
{
    vec2d wnd_size = region.ru_corner - region.ld_corner;

    if (wnd_size.y < HEADER_MENU_HEIGHT)
    {
        LOG_ERROR("CAN'T CREATE WINDOW: it's height = %lg < %lg\n",
                  wnd_size.y, HEADER_MENU_HEIGHT);
        return;
    }

    header_menu.set_region(rectangle_t(vec2d(0, wnd_size.y - HEADER_MENU_HEIGHT), wnd_size));
    header_menu.set_func  (move_window);
    header_menu.set_args  ((window_t *) this);
    header_menu.color = color_t::Orange;

    widget_manager_t:register_widget(&header_menu);
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_press(const mouse_context_t &context)
{
    mouse_context_t context_rel = context - region.ld_corner;

    if (!region.is_point_inside(context.pos)) return false;
    if (on_widgets_mouse_press (context_rel)) return true;

    return false;
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_release(const mouse_context_t &context)
{
    mouse_context_t context_rel = context - region.ld_corner;
    return on_widgets_mouse_release(context_rel);
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_move(const mouse_context_t &context)
{
    return on_widgets_mouse_move(context);
}

//--------------------------------------------------------------------------------------------------

bool move_window(void *window_, const widget_t::mouse_context_t &context)
{
    window_t *window = (window_t *) window_;
    window->region += context.pos;

    return true;
}
