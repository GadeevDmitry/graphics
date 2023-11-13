#include <stdio.h>
#include "menu/main_window_menu.h"

//==================================================================================================

const double main_window_menu_t::main_menu_btn_width = 50;

//==================================================================================================

main_window_menu_t::main_window_menu_t(window_controller_t &controller_, const color_t &color_):
menu_t                         (controller_, color_),
external_menu_button_controller(),
filter_menu                    (controller_, color_),
filter_btn                     (external_menu_button_controller, filter_menu, "Filters", color_)
{
    register_subwidget(&filter_btn);
}

//--------------------------------------------------------------------------------------------------

main_window_menu_t::main_window_menu_t(window_controller_t &controller_, const rectangle_t &enclosing_, const color_t &color_):
menu_t                         (controller_, color_),
external_menu_button_controller(),
filter_menu                    (controller_, color_),
filter_btn                     (external_menu_button_controller, filter_menu, "Filters", color_)
{
    register_subwidget(&filter_btn);
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void main_window_menu_t::create_buttons()
{
    rectangle_t menu_enclosing = enclosing;
    vec2d       menu_size      = menu_enclosing.get_size();

    filter_btn.text.color          = color_t::Black;
    filter_btn.text.character_size = 20;
    filter_btn.background          = color;

    filter_btn.enclosing = rectangle_t(
        menu_enclosing.ld_corner,
        main_menu_btn_width, menu_size.y
    );

    filter_menu.enclosing = rectangle_t(
        filter_btn.enclosing.lu_corner(),
        2*main_menu_btn_width, menu_size.y
    );
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
