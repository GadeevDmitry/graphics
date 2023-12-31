#include <stdio.h>

#include "window.h"
#include "button/close_button.h"
#include "data_structs/include/log.h"

//==================================================================================================

const color_t window_t::Light_theme  ( 0.871 , 0.871 , 0.871 );
const color_t window_t::Dark_theme   ( 0.243 , 0.243 , 0.259 );
const color_t window_t::Blue_theme   ( 0     , 0.478 , 0.800 );
const color_t window_t::Red_theme    ( 0.533 , 0     , 0     );

const double  window_t::header_menu_height = 50;

window_controller_t window_t::window_controller;

//==================================================================================================

bool window_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    handle->status = widget_t::WIDGET_ACTIVATED;
    handle->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

window_t::window_t(const color_t &color_, const char *wnd_name):
menu_t     (window_controller, color_, true),
header_menu(new window_header_menu_t(*this, wnd_name))
{
    register_subwidget(widget_proxy_t(header_menu));
}

//--------------------------------------------------------------------------------------------------

window_t::window_t(const rectangle_t &enclosing_, const color_t &color_, const char *wnd_name):
menu_t     (window_controller, color_, true),
header_menu(new window_header_menu_t(*this, wnd_name))
{
    register_subwidget(widget_proxy_t(header_menu));
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void window_t::create_header_menu()
{
    vec2d wnd_size = enclosing.get_size();
    if (wnd_size.y < header_menu_height)
    {
        LOG_ERROR("CAN'T CREATE WINDOW: height is too small for header menu (%lg < %lg)\n",
                  wnd_size.y, header_menu_height);
        return;
    }

    header_menu->create(rectangle_t(
        enclosing.ld_corner,
        enclosing.rd_corner() + vec2d(0, header_menu_height)));
}
