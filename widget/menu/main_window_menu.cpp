#include <stdio.h>
#include "menu/main_window_menu.h"

//==================================================================================================

const double main_window_menu_t::main_menu_btn_width = 60;

//==================================================================================================

main_window_menu_t::main_window_menu_t(window_controller_t &controller_, filter_manager_t &filter_manager, tool_manager_t &tool_manager):
menu_t                         (controller_, color_t::White),
external_menu_button_controller(),
filter_menu                    (controller_, filter_manager),
tool_menu                      (controller_, tool_manager  ),
palette_menu                   (controller_, tool_manager  ),
filter_btn                     (external_menu_button_controller, filter_menu , "Filters"),
tool_btn                       (external_menu_button_controller, tool_menu   , "Tools"  ),
palette_btn                    (external_menu_button_controller, palette_menu, "Colors" )
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

main_window_menu_t::main_window_menu_t(window_controller_t &controller_, const rectangle_t &enclosing_, filter_manager_t &filter_manager, tool_manager_t &tool_manager):
menu_t                         (controller_, color_t::White),
external_menu_button_controller(),
filter_menu                    (controller_, filter_manager),
tool_menu                      (controller_, tool_manager  ),
palette_menu                   (controller_, tool_manager  ),
filter_btn                     (external_menu_button_controller, filter_menu , "Filters"),
tool_btn                       (external_menu_button_controller, tool_menu   , "Tools"  ),
palette_btn                    (external_menu_button_controller, palette_menu, "Colors" )
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
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::create_buttons()
{
    const vec2d menu_size = enclosing.get_size();

    filter_btn .enclosing = rectangle_t(           enclosing.ld_corner  , main_menu_btn_width, menu_size.y);
    tool_btn   .enclosing = rectangle_t(filter_btn.enclosing.rd_corner(), main_menu_btn_width, menu_size.y);
    palette_btn.enclosing = rectangle_t(tool_btn  .enclosing.rd_corner(), main_menu_btn_width, menu_size.y);

    filter_btn .create_texture();
    tool_btn   .create_texture();
    palette_btn.create_texture();

    filter_menu .create(rectangle_t(filter_btn .enclosing.lu_corner(), external_filter_menu_t ::filter_menu_size .x, external_filter_menu_t ::filter_menu_size .y));
    tool_menu   .create(rectangle_t(tool_btn   .enclosing.lu_corner(), external_tool_menu_t   ::tool_menu_size   .x, external_tool_menu_t   ::tool_menu_size   .y));
    palette_menu.create(rectangle_t(palette_btn.enclosing.lu_corner(), external_palette_menu_t::palette_menu_size.x, external_palette_menu_t::palette_menu_size.y));
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
