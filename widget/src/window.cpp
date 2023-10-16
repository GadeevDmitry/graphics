#include <stdio.h>
#include "window.h"
#include "log.h"

//==================================================================================================

const color_t window_t::Light_theme  ( 0.871 , 0.871 , 0.871 );
const color_t window_t::Dark_theme   ( 0.243 , 0.243 , 0.259 );
const color_t window_t::Blue_theme   ( 0     , 0.478 , 0.800 );
const color_t window_t::Red_theme    ( 0.533 , 0     , 0     );

//==================================================================================================

static const double HEADER_MENU_HEIGHT = 50;

//==================================================================================================

window_t::window_t(const rectangle_t &region_, const color_t &color_):
widget_manager_t(nullptr, region_),
color           (color_),
header_menu     (button_t::button_delete)
{
    vec2d wnd_size = visible.region.ru_corner - visible.region.ld_corner;
    if (wnd_size.y < HEADER_MENU_HEIGHT)
    {
        LOG_ERROR("CAN'T CREATE WINDOW: it's height = %lg < %lg\n",
                  wnd_size.y, HEADER_MENU_HEIGHT);
        return;
    }

    create_header_menu();
}

//--------------------------------------------------------------------------------------------------

void window_t::create_header_menu()
{
    vec2d wnd_size = visible.region.get_size();

    rectangle_t header_menu_region(visible.region.ld_corner,
                                   visible.region.rd_corner() + vec2d(0, HEADER_MENU_HEIGHT));

    header_menu.set_region(header_menu_region);
    header_menu.set_funcs (nullptr, nullptr,
                           activate_by_mouse_click,
                           deactivate_by_mouse_click,
                           move_by_mouse_move);
    header_menu.set_args  (this);
    header_menu.color = color_t::White;

    header_menu_create_winapi_btn();

    register_subwidget(&header_menu);
}

//--------------------------------------------------------------------------------------------------

void window_t::header_menu_create_winapi_btn()
{
    rectangle_t header_region = header_menu.visible.region;
    vec2d       header_size   = header_region.get_size();

    texture_button_t *winapi = new texture_button_t(button_t::GREEN_WINAPI);

    vec2d  winapi_size  = winapi->texture.get_size();
    double winapi_scale = header_size.y / winapi_size.y;

    winapi_size = vec2d(winapi_size.x * winapi_scale, header_size.y);
    rectangle_t winapi_region(header_region.rd_corner() - vec2d(winapi_size.x, 0),
                              header_region.rd_corner() + vec2d(0, winapi_size.y));

    winapi->set_region(winapi_region);
    winapi->set_funcs(nullptr, nullptr, button_t::activate_by_mouse_click, button_t::close_by_mouse_click, nullptr);
    winapi->set_args (this);

    header_menu.register_button(winapi);
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_ASSERT(active == nullptr);

    const mouse_context_t &context = get_mouse_context();
    if (!visible.region.is_point_inside(context.pos))
        return false;

    if (on_subwidgets_mouse_press(btn))
        return true;

    status = WIDGET_UPDATED;
    update_ancestral_status(WIDGET_UPDATED);
    return true;
}
