#include <stdio.h>
#include "window.h"
#include "menu/window_header_menu.h"

//==================================================================================================

bool window_header_menu_controller_t::on_mouse_move(widget_t *handle, const eventable::mouse_context_t &context, const vec2d &off)
{
    (void) handle;
    (void) context;

    to_move.move(off);
    to_move.status = widget_t::WIDGET_ACTIVATED;
    to_move.update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

window_header_menu_t::window_header_menu_t(window_header_menu_controller_t &menu_controller, widget_t &to_close, const color_t &color_):
menu_t              (menu_controller, color_),
close_btn_controller(to_close),
close_btn           (close_btn_controller, close_button_t::GREEN)
{
    register_subwidget(&close_btn);
}

//--------------------------------------------------------------------------------------------------

window_header_menu_t::window_header_menu_t(window_header_menu_controller_t &menu_controller, widget_t &to_close, const rectangle_t &enclosing, const color_t &color_):
menu_t              (menu_controller, enclosing, color_),
close_btn_controller(to_close),
close_btn           (close_btn_controller, close_button_t::GREEN)
{
    register_subwidget(&close_btn);
    create_close_btn();
}

//--------------------------------------------------------------------------------------------------

void window_header_menu_t::create_close_btn()
{
    rectangle_t menu_enclosing = visible.enclosing;
    vec2d       menu_size      = menu_enclosing.get_size();

    vec2d  close_btn_size  = close_btn.texture->get_size();
    double close_btn_scale = menu_size.y / close_btn_size.y;

    close_btn_size = vec2d(close_btn_size.x * close_btn_scale, menu_size.y);
    close_btn.visible.enclosing = rectangle_t(
        menu_enclosing.rd_corner() - vec2d(close_btn_size.x, 0),
        menu_enclosing.rd_corner() + vec2d(0, close_btn_size.y));
}