#include <stdio.h>
#include "window/toolbar_window.h"

//==================================================================================================

const vec2d  toolbar_window_t::toolbar_size    (250, 450);
const vec2d  toolbar_window_t::toolbar_btn_size(100, 100);
const size_t toolbar_window_t::toolbar_btns_num = 8;

//==================================================================================================

#define toolbar_window_data_init(tool_manager)                                  \
buttons_controller(tool_manager),                                               \
btn_fill          (buttons_controller, nullptr, tool_button_t::FILL_OFF     ),  \
btn_rectangle     (buttons_controller, nullptr, tool_button_t::RECTANGLE_OFF),  \
btn_ellipse       (buttons_controller, nullptr, tool_button_t::ELLIPSE_OFF  ),  \
btn_polyline      (buttons_controller, nullptr, tool_button_t::POLYLINE_OFF ),  \
btn_pencil        (buttons_controller, nullptr, tool_button_t::PENCIL_OFF   ),  \
btn_line          (buttons_controller, nullptr, tool_button_t::LINE_OFF     ),  \
btn_rubber        (buttons_controller, nullptr, tool_button_t::RUBBER_OFF   ),  \
btn_spline        (buttons_controller, nullptr, tool_button_t::SPLINE_OFF   )

//==================================================================================================

toolbar_window_t::toolbar_window_t(window_controller_t &controller_, tool_manager_t &tool_manager, const color_t &color_):
window_t                (controller_, color_),
toolbar_window_data_init(tool_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

toolbar_window_t::toolbar_window_t(window_controller_t &controller_, tool_manager_t &tool_manager, const rectangle_t &enclosing, const color_t &color_):
window_t                (controller_, color_),
toolbar_window_data_init(tool_manager)
{
    register_buttons();
    create(enclosing);
}

//--------------------------------------------------------------------------------------------------

void toolbar_window_t::register_buttons()
{
    // reverse order
    register_subwidget(&btn_spline   );
    register_subwidget(&btn_rubber   );
    register_subwidget(&btn_line     );
    register_subwidget(&btn_pencil   );
    register_subwidget(&btn_polyline );
    register_subwidget(&btn_ellipse  );
    register_subwidget(&btn_rectangle);
    register_subwidget(&btn_fill     );
}

//--------------------------------------------------------------------------------------------------

void toolbar_window_t::set_tools(tool_t *fill  , tool_t *rectnagle, tool_t *ellipse, tool_t *polyline,
                                 tool_t *pencil, tool_t *line     , tool_t *rubber , tool_t *spline)
{
    btn_fill     .tool = fill;
    btn_rectangle.tool = rectnagle;
    btn_ellipse  .tool = ellipse;
    btn_polyline .tool = polyline;
    btn_pencil   .tool = pencil;
    btn_line     .tool = line;
    btn_rubber   .tool = rubber;
    btn_spline   .tool = spline;
}

//--------------------------------------------------------------------------------------------------

void toolbar_window_t::create_buttons()
{
    const vec2d wnd_size = visible.enclosing.get_size();
    if ((wnd_size.y < toolbar_size.y + header_menu_height) ||
        (wnd_size.x < toolbar_size.x))
    {
        LOG_ERROR("CAN'T CREATE WINDOW: size is too small for toolbar\n");
        return;
    }

    vec2d l_column_off(20,                                       header_menu_height + 10);
    vec2d r_column_off(toolbar_size.x - toolbar_btn_size.x - 20, header_menu_height + 10);

    size_t          cnt     = 0;
    tool_button_t **cnt_btn = (tool_button_t **) list_front(&subwidgets);

    for (; cnt < toolbar_btns_num / 2; ++cnt)
    {
        (**cnt_btn).visible.enclosing = rectangle_t(
            visible.enclosing.ld_corner + l_column_off,
            visible.enclosing.ld_corner + l_column_off + toolbar_btn_size
        );

        l_column_off.y += toolbar_btn_size.y + 10;
        cnt_btn = (tool_button_t **) list_next(cnt_btn);
    }

    for (; cnt < toolbar_btns_num; ++cnt)
    {
        (**cnt_btn).visible.enclosing = rectangle_t(
            visible.enclosing.ld_corner + r_column_off,
            visible.enclosing.ld_corner + r_column_off + toolbar_btn_size
        );

        r_column_off.y += toolbar_btn_size.y + 10;
        cnt_btn = (tool_button_t **) list_next(cnt_btn);
    }
}
