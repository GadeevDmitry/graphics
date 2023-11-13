#include <stdio.h>
#include "window/main_window.h"

//==================================================================================================

const double main_window_t::main_menu_height = 30;

//==================================================================================================

main_window_t::main_window_t(window_controller_t &controller_, filter_manager_t &filter_manager, const char *header_name, const color_t &color_):
window_t (controller_, header_name, color_),
main_menu(controller_, filter_manager)
{
    register_subwidget(&main_menu);
}

//--------------------------------------------------------------------------------------------------

main_window_t::main_window_t(window_controller_t &controller_, filter_manager_t &filter_manager, const rectangle_t &enclosing_, const char *header_name, const color_t &color_):
window_t (controller_, header_name, color_),
main_menu(controller_, filter_manager)
{
    register_subwidget(&main_menu);
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void main_window_t::create(const rectangle_t &enclosing)
{
    window_t::create(enclosing);
    main_menu.create(rectangle_t(
        enclosing.ld_corner + vec2d(0, header_menu_height),
        enclosing.get_size().x, main_menu_height
    ));
}
