#include <stdio.h>
#include "widget/window.h"
#include "menu/external_tool_menu.h"

//==================================================================================================

const vec2d  external_tool_menu_t::tool_menu_size(100, 240);
const vec2d  external_tool_menu_t::tool_btn_size (100, 30);
const size_t external_tool_menu_t::tool_btns_num = 8;

//==================================================================================================

#define tool_menu_data_init(tool_manager)                                   \
btn_controller(tool_manager),                                               \
btn_fill      (new external_tool_button_t(btn_controller, "Fill"     )),    \
btn_rectangle (new external_tool_button_t(btn_controller, "Rectangle")),    \
btn_ellipse   (new external_tool_button_t(btn_controller, "Ellipse"  )),    \
btn_polyline  (new external_tool_button_t(btn_controller, "Polyline" )),    \
btn_pencil    (new external_tool_button_t(btn_controller, "Pencil"   )),    \
btn_line      (new external_tool_button_t(btn_controller, "Line"     )),    \
btn_rubber    (new external_tool_button_t(btn_controller, "Rubber"   )),    \
btn_spline    (new external_tool_button_t(btn_controller, "Spline"   ))

//==================================================================================================

external_tool_menu_t::external_tool_menu_t(tool_manager_t &tool_manager):
menu_t(window_t::window_controller, color_t::White, true),
tool_menu_data_init(tool_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

external_tool_menu_t::external_tool_menu_t(const rectangle_t &enclosing_, tool_manager_t &tool_manager):
menu_t(window_t::window_controller, color_t::White, true),
tool_menu_data_init(tool_manager)
{
    register_buttons();
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void external_tool_menu_t::register_buttons()
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

void external_tool_menu_t::set_tools(ToolI *fill  , ToolI *rectnagle, ToolI *ellipse, ToolI *polyline,
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

void external_tool_menu_t::create_buttons()
{
    const vec2d menu_size = enclosing.get_size();
    if ((menu_size.y < tool_menu_size.y) ||
        (menu_size.x < tool_menu_size.x))
    {
        LOG_ERROR("CAN'T CREATE MENU: size is too small for tool menu\n");
        return;
    }

    vec2d tool_btn_off(0, 0);

    size_t          cnt     = 0;
    widget_proxy_t *cnt_btn = (widget_proxy_t *) list_front(&subwidgets); 

    for (; cnt < tool_btns_num; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        external_tool_button_t *cnt_tool_btn = (external_tool_button_t *) cnt_btn->internal;

        cnt_tool_btn->enclosing = rectangle_t(
            enclosing.ld_corner + tool_btn_off,
            enclosing.ld_corner + tool_btn_off + tool_btn_size
        );

        cnt_tool_btn->create_texture();

        tool_btn_off.y += tool_btn_size.y;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }
}

//--------------------------------------------------------------------------------------------------

void external_tool_menu_t::add_tool(ToolI *tool, const char *tool_name)
{
    external_tool_button_t *tool_btn = new external_tool_button_t(btn_controller, tool_name, tool);

    tool_btn->enclosing = rectangle_t(enclosing.lu_corner(), tool_btn_size.x, tool_btn_size.y);
    enclosing.ru_corner = tool_btn->enclosing.ru_corner;

    tool_btn->create_texture();
    register_subwidget(widget_proxy_t(tool_btn));
}
