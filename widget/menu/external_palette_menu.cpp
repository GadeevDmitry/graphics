#include <stdio.h>
#include "menu/external_palette_menu.h"

//==================================================================================================

const vec2d  external_palette_menu_t::palette_menu_size(100, 180);
const vec2d  external_palette_menu_t::palette_btn_size (100, 30);
const size_t external_palette_menu_t::palette_btns_num = 6;

//==================================================================================================

#define palette_menu_data_init(tool_manager)                                                        \
buttons_controller(tool_manager),                                                                   \
btn_white         (new external_palette_button_t(buttons_controller, "White" , color_t::White )),   \
btn_blue          (new external_palette_button_t(buttons_controller, "Blue"  , color_t::Blue  )),   \
btn_red           (new external_palette_button_t(buttons_controller, "Red"   , color_t::Red   )),   \
btn_orange        (new external_palette_button_t(buttons_controller, "Orange", color_t::Orange)),   \
btn_green         (new external_palette_button_t(buttons_controller, "Green" , color_t::Green )),   \
btn_black         (new external_palette_button_t(buttons_controller, "Black" , color_t::Black ))

//==================================================================================================

external_palette_menu_t::external_palette_menu_t(widget_controller_t &controller_, tool_manager_t &tool_manager):
menu_t(controller_, color_t::White, true),
palette_menu_data_init(tool_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

external_palette_menu_t::external_palette_menu_t(widget_controller_t &controller_, const rectangle_t &enclosing_, tool_manager_t &tool_manager):
menu_t(controller_, color_t::White, true),
palette_menu_data_init(tool_manager)
{
    register_buttons();
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void external_palette_menu_t::register_buttons()
{
    // reverse order for right create_buttons() work
    register_subwidget(widget_proxy_t(btn_black ));
    register_subwidget(widget_proxy_t(btn_green ));
    register_subwidget(widget_proxy_t(btn_orange));
    register_subwidget(widget_proxy_t(btn_red   ));
    register_subwidget(widget_proxy_t(btn_blue  ));
    register_subwidget(widget_proxy_t(btn_white ));
}

//--------------------------------------------------------------------------------------------------

void external_palette_menu_t::create_buttons()
{
    const vec2d menu_size = enclosing.get_size();
    if ((menu_size.y < palette_menu_size.y) ||
        (menu_size.x < palette_menu_size.x))
    {
        LOG_ERROR("CAN'T CREATE MENU: size is too small for palette menu\n");
        return;
    }

    vec2d tool_btn_off(0, 0);

    size_t          cnt     = 0;
    widget_proxy_t *cnt_btn = (widget_proxy_t *) list_front(&subwidgets); 

    for (; cnt < palette_btns_num; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        external_palette_button_t *cnt_palette_btn = (external_palette_button_t *) cnt_btn->internal;

        cnt_palette_btn->enclosing = rectangle_t(
            enclosing.ld_corner + tool_btn_off,
            enclosing.ld_corner + tool_btn_off + palette_btn_size
        );

        cnt_palette_btn->create_texture();

        tool_btn_off.y += palette_btn_size.y;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }
}
