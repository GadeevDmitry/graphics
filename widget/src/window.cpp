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

//--------------------------------------------------------------------------------------------------

static void header_menu_mouse_move_func  (menu_t *self, void *args, const vec2d &off, widget_t *&active);
static void header_menu_create_winapi_btn(menu_t &header_menu, widget_t *window);

//==================================================================================================

window_t::window_t(const rectangle_t &region_, const color_t &color_):
widget_manager_t(nullptr, region_),
region          (region_),
header_menu     (button_t::button_delete),
color           (color_)
{
    vec2d wnd_size = region.ru_corner - region.ld_corner;
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
    vec2d wnd_size = region.get_size();

    rectangle_t header_menu_region(region.ld_corner,
                                   region.rd_corner() + vec2d(0, HEADER_MENU_HEIGHT));

    header_menu.set_region(header_menu_region);
    header_menu.set_funcs (nullptr, nullptr,
                           menu_t::activate_by_mouse_click,
                           menu_t::deactivate_by_mouse_click,
                           header_menu_mouse_move_func);
    header_menu.set_args  (this);
    header_menu.color = color_t::White;

    header_menu_create_winapi_btn(header_menu, this);

    register_widget(&header_menu);
}

//--------------------------------------------------------------------------------------------------

static void header_menu_create_winapi_btn(menu_t &header_menu, widget_t *window)
{
    rectangle_t header_region = header_menu.get_region();
    vec2d       header_size   = header_region.get_size();

    LOG_TAB_SERVICE_MESSAGE("header_menu_create_winapi_btn", "\n");
    LOG_TAB++;
    LOG_TAB_SERVICE_MESSAGE("header_menu_region:", "\n");
    rectangle_t::dump(&header_region);

    texture_button_t *winapi = new texture_button_t(button_t::GREEN_WINAPI);

    vec2d  winapi_size  = winapi->texture.get_size();
    double winapi_scale = header_size.y / winapi_size.y;

    winapi_size = vec2d(winapi_size.x * winapi_scale, header_size.y);
    rectangle_t winapi_region(header_region.rd_corner() - vec2d(winapi_size.x, 0),
                              header_region.rd_corner() + vec2d(0, winapi_size.y));

    LOG_TAB_MESSAGE("winapi size   = {%lg, %lg}\n", winapi_size.x, winapi_size.y);
    LOG_TAB_MESSAGE("winapi region:\n");
    rectangle_t::dump(&winapi_region);

    winapi->set_region(winapi_region);
    winapi->set_funcs(nullptr, nullptr, button_t::activate_by_mouse_click, button_t::close_by_mouse_click, nullptr);
    winapi->set_args (window);

    header_menu.register_button(winapi);

    LOG_TAB--;
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    const mouse_context_t &context = get_mouse_context();

    if (!region.is_point_inside(context.pos))
        return false;

    on_widgets_mouse_press(btn);
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
