#include <stdio.h>
#include "window/toolbar_window.h"

//==================================================================================================

const vec2d  toolbar_window_t::toolbar_size    (250, 450);
const vec2d  toolbar_window_t::toolbar_btn_size(100, 100);
const size_t toolbar_window_t::toolbar_btns_num = 8;

//==================================================================================================

#define toolbar_window_data_init(tool_manager)                                              \
buttons_controller(tool_manager),                                                           \
btn_fill          (new tool_button_t(buttons_controller, tool_button_t::FILL_OFF     )),    \
btn_rectangle     (new tool_button_t(buttons_controller, tool_button_t::RECTANGLE_OFF)),    \
btn_ellipse       (new tool_button_t(buttons_controller, tool_button_t::ELLIPSE_OFF  )),    \
btn_polyline      (new tool_button_t(buttons_controller, tool_button_t::POLYLINE_OFF )),    \
btn_pencil        (new tool_button_t(buttons_controller, tool_button_t::PENCIL_OFF   )),    \
btn_line          (new tool_button_t(buttons_controller, tool_button_t::LINE_OFF     )),    \
btn_rubber        (new tool_button_t(buttons_controller, tool_button_t::RUBBER_OFF   )),    \
btn_spline        (new tool_button_t(buttons_controller, tool_button_t::SPLINE_OFF   ))

//==================================================================================================

toolbar_window_t::toolbar_window_t(window_controller_t &controller_, tool_manager_t &tool_manager, const color_t &color_, const char *wnd_name):
window_t                (controller_, color_, wnd_name),
toolbar_window_data_init(tool_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

toolbar_window_t::toolbar_window_t(window_controller_t &controller_, const rectangle_t &enclosing_, tool_manager_t &tool_manager, const color_t &color_, const char *wnd_name):
window_t                (controller_, color_, wnd_name),
toolbar_window_data_init(tool_manager)
{
    register_buttons();
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void toolbar_window_t::register_buttons()
{
    // reverse order for right create_buttons() work
    register_subwidget(widget_proxy_t(btn_spline   ));
    register_subwidget(widget_proxy_t(btn_rubber   ));
    register_subwidget(widget_proxy_t(btn_line     ));
    register_subwidget(widget_proxy_t(btn_pencil   ));
    register_subwidget(widget_proxy_t(btn_polyline ));
    register_subwidget(widget_proxy_t(btn_ellipse  ));
    register_subwidget(widget_proxy_t(btn_rectangle));
    register_subwidget(widget_proxy_t(btn_fill     ));
}

//--------------------------------------------------------------------------------------------------

void toolbar_window_t::set_tools(ToolI *fill  , ToolI *rectnagle, ToolI *ellipse, ToolI *polyline,
                                 ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline)
{
    btn_fill     ->tool = fill;
    btn_rectangle->tool = rectnagle;
    btn_ellipse  ->tool = ellipse;
    btn_polyline ->tool = polyline;
    btn_pencil   ->tool = pencil;
    btn_line     ->tool = line;
    btn_rubber   ->tool = rubber;
    btn_spline   ->tool = spline;
}

//--------------------------------------------------------------------------------------------------

void toolbar_window_t::create_buttons()
{
    const vec2d wnd_size = enclosing.get_size();
    if ((wnd_size.y < toolbar_size.y + header_menu_height) ||
        (wnd_size.x < toolbar_size.x))
    {
        LOG_ERROR("CAN'T CREATE WINDOW: size is too small for toolbar\n");
        return;
    }

    vec2d l_column_off(20,                                       header_menu_height + 10);
    vec2d r_column_off(toolbar_size.x - toolbar_btn_size.x - 20, header_menu_height + 10);

    size_t          cnt     = 0;
    widget_proxy_t *cnt_btn = (widget_proxy_t *) list_front(&subwidgets);

    for (; cnt < toolbar_btns_num / 2; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        tool_button_t *cnt_tool_btn = (tool_button_t *) cnt_btn->internal;

        cnt_tool_btn->enclosing = rectangle_t(
            enclosing.ld_corner + l_column_off,
            enclosing.ld_corner + l_column_off + toolbar_btn_size
        );

        l_column_off.y += toolbar_btn_size.y + 10;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }

    for (; cnt < toolbar_btns_num; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        tool_button_t *cnt_tool_btn = (tool_button_t *) cnt_btn->internal;

        cnt_tool_btn->enclosing = rectangle_t(
            enclosing.ld_corner + r_column_off,
            enclosing.ld_corner + r_column_off + toolbar_btn_size
        );

        r_column_off.y += toolbar_btn_size.y + 10;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }
}
