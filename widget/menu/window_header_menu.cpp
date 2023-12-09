#include <stdio.h>
#include "window.h"
#include "menu/window_header_menu.h"

//==================================================================================================

window_header_menu_controller_t window_header_menu_t::window_header_menu_controller;

//==================================================================================================

bool window_header_menu_controller_t::on_mouse_move(widget_t *handle, const eventable::mouse_context_t &context, const vec2d &off)
{
    (void) handle;
    (void) context;

    window_header_menu_t *window_header_menu = (window_header_menu_t *) handle;
    window_header_menu->window.move(off);
    window_header_menu->window.status = widget_t::WIDGET_ACTIVATED;
    window_header_menu->window.update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

window_header_menu_t::window_header_menu_t(window_t &wnd, const char *wnd_name):
menu_t              (window_header_menu_controller, color_t::White),
close_btn           (wnd, close_button_t::GREEN),
window              (wnd),
window_name         (wnd_name, 30)
{
    register_subwidget(widget_proxy_t(&window_name));
    register_subwidget(widget_proxy_t(&close_btn  ));
}

//--------------------------------------------------------------------------------------------------

window_header_menu_t::window_header_menu_t(const rectangle_t &enclosing_, window_t &wnd, const char *wnd_name):
menu_t              (window_header_menu_controller, color_t::White),
close_btn           (wnd, close_button_t::GREEN),
window              (wnd),
window_name         (wnd_name, 30)
{
    register_subwidget(widget_proxy_t(&window_name));
    register_subwidget(widget_proxy_t(&close_btn  ));
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void window_header_menu_t::create_close_btn()
{
    rectangle_t menu_enclosing = enclosing;
    vec2d       menu_size      = menu_enclosing.get_size();

    vec2d  close_btn_size  = close_btn.texture->get_size();
    double close_btn_scale = menu_size.y / close_btn_size.y;

    close_btn_size = vec2d(close_btn_size.x * close_btn_scale, menu_size.y);
    close_btn.enclosing = rectangle_t(
        menu_enclosing.rd_corner() - vec2d(close_btn_size.x, 0),
        menu_enclosing.rd_corner() + vec2d(0, close_btn_size.y));
}

//--------------------------------------------------------------------------------------------------

void window_header_menu_t::create_window_name()
{
    rectangle_t menu_enclosing = enclosing;

    window_name.enclosing = rectangle_t(
        menu_enclosing.ld_corner,
        close_btn.enclosing.lu_corner());

    window_name.create_texture();
}
