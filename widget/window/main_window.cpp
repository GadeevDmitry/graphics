#include <stdio.h>
#include "window/main_window.h"

//==================================================================================================

const double main_window_t::main_menu_height = 30;

//==================================================================================================

main_window_t::main_window_t(event_manager_t &event_manager, tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color_, const char *wnd_name):
window_t (color_, wnd_name),
main_menu(new main_window_menu_t(*this, event_manager, filter_manager, tool_manager))
{
    register_subwidget(widget_proxy_t(main_menu));
}

//--------------------------------------------------------------------------------------------------

main_window_t::main_window_t(const rectangle_t &enclosing_, event_manager_t &event_manager, tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color_, const char *wnd_name):
window_t (color_, wnd_name),
main_menu(new main_window_menu_t(*this, event_manager, filter_manager, tool_manager))
{
    register_subwidget(widget_proxy_t(main_menu));
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void main_window_t::create(const rectangle_t &enclosing_)
{
    window_t::create(enclosing_);
    main_menu->create(rectangle_t(
        enclosing_.ld_corner + vec2d(0, header_menu_height),
        enclosing_.get_size().x, main_menu_height
    ));
}
