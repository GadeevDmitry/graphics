#include <stdio.h>
#include "window/palette_window.h"

//==================================================================================================

const vec2d  palette_window_t::palette_size    (250, 340);
const vec2d  palette_window_t::palette_btn_size(100, 100);
const size_t palette_window_t::palette_btns_num = 6;

//==================================================================================================

#define palette_window_data_init(tool_manager)                                                                  \
buttons_controller(tool_manager),                                                                               \
btn_white         (new palette_button_t(buttons_controller, palette_button_t::WHITE_OFF , color_t::White )),    \
btn_blue          (new palette_button_t(buttons_controller, palette_button_t::BLUE_OFF  , color_t::Blue  )),    \
btn_red           (new palette_button_t(buttons_controller, palette_button_t::RED_OFF   , color_t::Red   )),    \
btn_orange        (new palette_button_t(buttons_controller, palette_button_t::ORANGE_OFF, color_t::Orange)),    \
btn_green         (new palette_button_t(buttons_controller, palette_button_t::GREEN_OFF , color_t::Green )),    \
btn_black         (new palette_button_t(buttons_controller, palette_button_t::BLACK_OFF , color_t::Black ))

//==================================================================================================

palette_window_t::palette_window_t(window_controller_t &controller_, tool_manager_t &tool_manager, const color_t &color_, const char *wnd_name):
window_t                (controller_, color_, wnd_name),
palette_window_data_init(tool_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

palette_window_t::palette_window_t(window_controller_t &controller_, const rectangle_t &enclosing_, tool_manager_t &tool_manager, const color_t &color_, const char *wnd_name):
window_t                (controller_, color_, wnd_name),
palette_window_data_init(tool_manager)
{
    register_buttons();
    create(enclosing_);
}

//--------------------------------------------------------------------------------------------------

void palette_window_t::register_buttons()
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

void palette_window_t::create_buttons()
{
    const vec2d wnd_size = enclosing.get_size();
    if ((wnd_size.y < palette_size.y + header_menu_height) ||
        (wnd_size.x < palette_size.x))
    {
        LOG_ERROR("CAN'T CREATE WINDOW: size is too small for palette\n");
        return;
    }

    vec2d l_column_off(20,                                       header_menu_height + 10);
    vec2d r_column_off(palette_size.x - palette_btn_size.x - 20, header_menu_height + 10);

    size_t          cnt     = 0;
    widget_proxy_t *cnt_btn = (widget_proxy_t *) list_front(&subwidgets);

    for (; cnt < palette_btns_num / 2; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        palette_button_t *cnt_palette_btn = (palette_button_t *) cnt_btn->internal;

        cnt_palette_btn->enclosing = rectangle_t(
            enclosing.ld_corner + l_column_off,
            enclosing.ld_corner + l_column_off + palette_btn_size
        );

        l_column_off.y += palette_btn_size.y + 10;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }

    for (; cnt < palette_btns_num; ++cnt)
    {
        LOG_ASSERT(cnt_btn->is_internal);

        palette_button_t *cnt_palette_btn = (palette_button_t *) cnt_btn->internal;

        cnt_palette_btn->enclosing = rectangle_t(
            enclosing.ld_corner + r_column_off,
            enclosing.ld_corner + r_column_off + palette_btn_size
        );

        r_column_off.y += palette_btn_size.y + 10;
        cnt_btn = (widget_proxy_t *) list_next(cnt_btn);
    }
}
