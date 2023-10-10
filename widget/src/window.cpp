#include <stdio.h>
#include "window.h"
#include "log.h"

//==================================================================================================

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
    header_menu.color = color_t::Orange;
    widget_manager_t:register_widget(&header_menu);
}
