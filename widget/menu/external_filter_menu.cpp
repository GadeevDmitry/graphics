#include <stdio.h>
#include "menu/external_filter_menu.h"

//==================================================================================================

const vec2d  external_filter_menu_t::filter_menu_size(100, 60);
const vec2d  external_filter_menu_t::filter_btn_size (100, 30);
const size_t external_filter_menu_t::filter_btns_num = 2;

//==================================================================================================

#define filter_menu_data_init(root, event_manager, filter_manager)          \
btn_controller(root, event_manager, filter_manager),                        \
btn_brightness(new external_filter_button_t(btn_controller, "Brightness")), \
btn_russian   (new external_filter_button_t(btn_controller, "Russian"))

//==================================================================================================

external_filter_menu_t::external_filter_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager):
menu_t               (window_t::window_controller, color_t::White, true),
filter_menu_data_init(root, event_manager, filter_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

external_filter_menu_t::external_filter_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager, const rectangle_t &enclosing_):
menu_t               (window_t::window_controller, color_t::White, true),
filter_menu_data_init(root, event_manager, filter_manager)
{
    register_buttons();
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void external_filter_menu_t::register_buttons()
{
    // reverse order for right create_buttons() work
    register_subwidget(widget_proxy_t(btn_russian));
    register_subwidget(widget_proxy_t(btn_brightness));
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

    size_t          cnt     = 0;
    widget_proxy_t *cnt_btn = (widget_proxy_t *) list_front(&subwidgets);

    for (; cnt < filter_btns_num; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        external_filter_button_t *cnt_filter_btn = (external_filter_button_t *) cnt_btn->internal;

        cnt_filter_btn->enclosing = rectangle_t(
            enclosing.ld_corner + filter_btn_off,
            enclosing.ld_corner + filter_btn_off + filter_btn_size
        );

        cnt_filter_btn->create_texture();

        filter_btn_off.y += filter_btn_size.y;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }
}

//--------------------------------------------------------------------------------------------------

void external_filter_menu_t::add_filter(FilterI *filter, const char *filter_name)
{
    external_filter_button_t *filter_btn = new external_filter_button_t(btn_controller, filter_name, filter);

    filter_btn->enclosing = rectangle_t(enclosing.lu_corner(), filter_btn_size.x, filter_btn_size.y);
    enclosing.ru_corner   = filter_btn->enclosing.ru_corner;

    filter_btn->create_texture();
    register_subwidget(widget_proxy_t(filter_btn));
}
