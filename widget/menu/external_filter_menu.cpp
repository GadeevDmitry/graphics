#include <stdio.h>
#include "menu/external_filter_menu.h"

//==================================================================================================

const vec2d  external_filter_menu_t::filter_menu_size(100, 30);
const vec2d  external_filter_menu_t::filter_btn_size (100, 30);
const size_t external_filter_menu_t::filter_btns_num = 1;

//==================================================================================================

#define filter_menu_data_init(filter_manager)        \
buttons_controller(filter_manager),                  \
btn_brightness    (buttons_controller, "Brightness")

//==================================================================================================

external_filter_menu_t::external_filter_menu_t(widget_controller_t &controller_, filter_manager_t &filter_manager, const color_t &color_):
menu_t               (controller_, color_),
filter_menu_data_init(filter_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

external_filter_menu_t::external_filter_menu_t(widget_controller_t &controller_, filter_manager_t &filter_manager, const rectangle_t &enclosing, const color_t &color_):
menu_t               (controller_, color_),
filter_menu_data_init(filter_manager)
{
    register_buttons();
    create(enclosing);
}

//--------------------------------------------------------------------------------------------------

void external_filter_menu_t::register_buttons()
{
    // reverse order for right create_buttons() work
    register_subwidget(&btn_brightness);
}

//--------------------------------------------------------------------------------------------------

void external_filter_menu_t::create_buttons()
{
    const vec2d menu_size = enclosing.get_size();
    if ((menu_size.y < filter_menu_size.y) ||
        (menu_size.x < filter_menu_size.x))
    {
        LOG_ERROR("CAN'T CREATE MENU: size is too small for filter menu\n");
        return;
    }

    vec2d filter_btn_off(0, 0);

    size_t            cnt     = 0;
    filter_button_t **cnt_btn = (filter_button_t **) list_front(&subwidgets);

    for (; cnt < filter_btns_num; ++cnt)
    {
        (**cnt_btn).enclosing = rectangle_t(
            enclosing.ld_corner + filter_btn_off,
            enclosing.ld_corner + filter_btn_off + filter_btn_size
        );

        filter_btn_off.y += filter_btn_size.y;
        cnt_btn = (filter_button_t **) list_next(cnt_btn);
    }
}
