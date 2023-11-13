#include <stdio.h>
#include "menu/main_window_menu.h"

//==================================================================================================

const double main_window_menu_t::main_menu_btn_width = 50;

//==================================================================================================

main_window_menu_t::main_window_menu_t(window_controller_t &controller_, filter_manager_t &filter_manager):
menu_t                         (controller_, color_t::White),
external_menu_button_controller(),
filter_menu                    (controller_, filter_manager),
filter_btn                     (external_menu_button_controller, filter_menu, "Filters")
{
    register_subwidget(&filter_btn);
}

//--------------------------------------------------------------------------------------------------

main_window_menu_t::main_window_menu_t(window_controller_t &controller_, filter_manager_t &filter_manager, const rectangle_t &enclosing_):
menu_t                         (controller_, color_t::White),
external_menu_button_controller(),
filter_menu                    (controller_, filter_manager),
filter_btn                     (external_menu_button_controller, filter_menu, "Filters")
{
    register_subwidget(&filter_btn);
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::create_buttons()
{
    rectangle_t menu_enclosing = enclosing;
    vec2d       menu_size      = menu_enclosing.get_size();

    filter_btn.enclosing = rectangle_t(
        menu_enclosing.ld_corner,
        main_menu_btn_width, menu_size.y
    );

    filter_menu.create(rectangle_t(
        filter_btn.enclosing.lu_corner(),
        external_filter_menu_t::filter_menu_size.x, external_filter_menu_t::filter_menu_size.y
    ));
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::recalc_regions()
{
    subwidgets_recalc_regions();

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        sub_enclosing |= (**cnt).sub_enclosing;
    }
}
