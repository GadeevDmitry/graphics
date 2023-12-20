#include <stdio.h>
#include "menu/main_window_menu.h"

//==================================================================================================

const double main_window_menu_t::main_menu_btn_width = 80;

//==================================================================================================

main_window_menu_t::main_window_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager, tool_manager_t &tool_manager):
menu_t      (window_t::window_controller, color_t::White),
filter_menu (root, event_manager, filter_manager),
tool_menu   (tool_manager  ),
palette_menu(tool_manager  ),
canvas_menu (),
filter_btn  (filter_menu , "Filters"),
tool_btn    (tool_menu   , "Tools"  ),
palette_btn (palette_menu, "Colors" ),
canvas_btn  (canvas_menu , "Windows")
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

main_window_menu_t::main_window_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager, tool_manager_t &tool_manager, const rectangle_t &enclosing_):
menu_t      (window_t::window_controller, color_t::White),
filter_menu (root, event_manager, filter_manager),
tool_menu   (tool_manager  ),
palette_menu(tool_manager  ),
canvas_menu (),
filter_btn  (filter_menu , "Filters"),
tool_btn    (tool_menu   , "Tools"  ),
palette_btn (palette_menu, "Colors" ),
canvas_btn  (canvas_menu , "Windows")
{
    register_buttons();
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::register_buttons()
{
    register_subwidget(widget_proxy_t(&filter_btn ));
    register_subwidget(widget_proxy_t(&tool_btn   ));
    register_subwidget(widget_proxy_t(&palette_btn));
    register_subwidget(widget_proxy_t(&canvas_btn ));
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::create_buttons()
{
    const vec2d menu_size = enclosing.get_size();

    filter_btn .enclosing = rectangle_t(            enclosing.ld_corner  , main_menu_btn_width, menu_size.y);
    tool_btn   .enclosing = rectangle_t(filter_btn .enclosing.rd_corner(), main_menu_btn_width, menu_size.y);
    palette_btn.enclosing = rectangle_t(tool_btn   .enclosing.rd_corner(), main_menu_btn_width, menu_size.y);
    canvas_btn .enclosing = rectangle_t(palette_btn.enclosing.rd_corner(), main_menu_btn_width, menu_size.y);

    filter_btn .create_texture();
    tool_btn   .create_texture();
    palette_btn.create_texture();
    canvas_btn .create_texture();

    filter_menu .create(rectangle_t(filter_btn .enclosing.lu_corner(), external_filter_menu_t ::filter_menu_size .x, external_filter_menu_t ::filter_menu_size .y));
    tool_menu   .create(rectangle_t(tool_btn   .enclosing.lu_corner(), external_tool_menu_t   ::tool_menu_size   .x, external_tool_menu_t   ::tool_menu_size   .y));
    palette_menu.create(rectangle_t(palette_btn.enclosing.lu_corner(), external_palette_menu_t::palette_menu_size.x, external_palette_menu_t::palette_menu_size.y));
    canvas_menu .create(rectangle_t(canvas_btn .enclosing.lu_corner(), external_canvas_menu_t ::canvas_menu_size .x, external_canvas_menu_t ::canvas_menu_size .y));
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::recalc_regions()
{
    subwidgets_recalc_regions();

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        LOG_ASSERT(cnt->is_internal);
        sub_enclosing |= cnt->internal->sub_enclosing;
    }
}
