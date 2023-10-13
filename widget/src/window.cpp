#include <stdio.h>
#include "window.h"
#include "log.h"

//==================================================================================================

static const double HEADER_MENU_HEIGHT = 30;

//--------------------------------------------------------------------------------------------------

static void header_menu_mouse_move_func(menu_t *self, void *args, const vec2d &off, widget_t *&active);

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

    rectangle_t header_menu_region(vec2d(0, 0), vec2d(wnd_size.x, HEADER_MENU_HEIGHT));
    header_menu_region += (region.lu_corner() - vec2d(0, HEADER_MENU_HEIGHT));

    header_menu.set_region(header_menu_region);
    header_menu.set_funcs (nullptr, nullptr,
                           menu_t::activate_by_mouse_click,
                           menu_t::deactivate_by_mouse_click,
                           header_menu_mouse_move_func);
    header_menu.set_args  (this);
    header_menu.color = color_t::Orange;

    register_widget(&header_menu);

    LOG_MESSAGE("<<<<<<<<<<<<<<<<\n"
                "window        = %p\n"
                "header_menu   = %p\n"
                "widgets.front = %p\n"
                ">>>>>>>>>>>>>>>>\n", this, &header_menu, *(widget_t **) list_front(&widgets));

}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    const mouse_context_t &context = get_mouse_context();

    LOG_TAB_SERVICE_MESSAGE("WINDOW_T::ON_MOUSE_PRESS", "\n");
    LOG_TAB++;

    if (!region.is_point_inside(context.pos))
    {
        LOG_TAB_MESSAGE("POINT {%lg, %lg} IS NOT INSIDE\n", context.pos.x, context.pos.y);
        LOG_TAB--;
        return false;
    }

    on_widgets_mouse_press(btn);
    LOG_TAB--;
    return true;
}

//--------------------------------------------------------------------------------------------------

static void header_menu_mouse_move_func(menu_t *self, void *args, const vec2d &off, widget_t *&active)
{
    (void) self;
    (void) active;

    window_t *parent = (window_t *) args;
    parent->move(off);
}
