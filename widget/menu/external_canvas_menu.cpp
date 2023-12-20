#include <stdio.h>
#include "widget/window.h"
#include "menu/external_canvas_menu.h"

//==================================================================================================

const vec2d  external_canvas_menu_t::canvas_menu_size(100,  0);
const vec2d  external_canvas_menu_t::canvas_btn_size (100, 30);
const size_t external_canvas_menu_t::canvas_btns_num = 0;

//==================================================================================================

external_canvas_menu_t::external_canvas_menu_t():
menu_t        (window_t::window_controller, color_t::White, true),
btn_controller()
{}

//--------------------------------------------------------------------------------------------------

external_canvas_menu_t::external_canvas_menu_t(const rectangle_t &enclosing_):
menu_t        (window_t::window_controller, color_t::White, true),
btn_controller()
{
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void external_canvas_menu_t::register_canvas(canvas_window_t *canvas_wnd, const char *canvas_name)
{
    external_canvas_button_t *canvas_btn = new external_canvas_button_t(btn_controller, canvas_name, canvas_wnd);

    canvas_btn->enclosing = rectangle_t(enclosing.lu_corner(), canvas_btn_size.x, canvas_btn_size.y);
    enclosing.ru_corner   = canvas_btn->enclosing.ru_corner;

    canvas_btn->create_texture();
    register_subwidget(widget_proxy_t(canvas_btn));
}

//--------------------------------------------------------------------------------------------------

void external_canvas_menu_t::unregister_canvas(canvas_window_t *canvas_wnd)
{
    widget_proxy_t *child = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (size_t cnt = 0; child != fict; ++cnt)
    {
        LOG_ASSERT(child->is_internal);
        external_canvas_button_t * canvas_btn = (external_canvas_button_t *) child->internal;

        if (canvas_btn->canvas_window == canvas_wnd)
        {
            list_erase(&subwidgets, cnt);
            return;
        }

        child = (widget_proxy_t *) list_next(child);
    }
}
