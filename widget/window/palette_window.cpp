#include <stdio.h>
#include "window/palette_window.h"

//==================================================================================================

const vec2d  palette_window_t::palette_size    (250, 340);
const vec2d  palette_window_t::palette_btn_size(100, 100);
const size_t palette_window_t::palette_btns_num = 6;

//==================================================================================================

#define palette_window_data_init(tool_manager)                                          \
buttons_controller(tool_manager),                                                       \
btn_white         (buttons_controller, color_t::White , palette_button_t::WHITE_OFF ),  \
btn_blue          (buttons_controller, color_t::Blue  , palette_button_t::BLUE_OFF  ),  \
btn_red           (buttons_controller, color_t::Red   , palette_button_t::RED_OFF   ),  \
btn_orange        (buttons_controller, color_t::Orange, palette_button_t::ORANGE_OFF),  \
btn_green         (buttons_controller, color_t::Green , palette_button_t::GREEN_OFF ),  \
btn_black         (buttons_controller, color_t::Black , palette_button_t::BLACK_OFF )

//==================================================================================================

palette_window_t::palette_window_t(window_controller_t &controller_, tool_manager_t &tool_manager, const color_t &color_):
window_t                (controller_, color_),
palette_window_data_init(tool_manager)
{
    register_buttons();
}

//--------------------------------------------------------------------------------------------------

palette_window_t::palette_window_t(window_controller_t &controller_, tool_manager_t &tool_manager, const rectangle_t &enclosing, const color_t &color_):
window_t                (controller_, color_),
palette_window_data_init(tool_manager)
{
    register_buttons();
    create(enclosing);
}

//--------------------------------------------------------------------------------------------------

void palette_window_t::register_buttons()
{
    // reverse order
    register_subwidget(&btn_black );
    register_subwidget(&btn_green );
    register_subwidget(&btn_orange);
    register_subwidget(&btn_red   );
    register_subwidget(&btn_blue  );
    register_subwidget(&btn_white );
}

//--------------------------------------------------------------------------------------------------

void palette_window_t::create_buttons()
{
    const vec2d wnd_size = visible.enclosing.get_size();
    if ((wnd_size.y < palette_size.y + header_menu_height) ||
        (wnd_size.x < palette_size.x))
    {
        LOG_ERROR("CAN'T CREATE WINDOW: size is too small for palette\n");
        return;
    }

    vec2d l_column_off(20,                                       header_menu_height + 10);
    vec2d r_column_off(palette_size.x - palette_btn_size.x - 20, header_menu_height + 10);

    size_t             cnt     = 0;
    palette_button_t **cnt_btn = (palette_button_t **) list_front(&subwidgets);

    for (; cnt < palette_btns_num / 2; ++cnt)
    {
        (**cnt_btn).visible.enclosing = rectangle_t(
            visible.enclosing.ld_corner + l_column_off,
            visible.enclosing.ld_corner + l_column_off + palette_btn_size
        );

        l_column_off.y += palette_btn_size.y + 10;
        cnt_btn = (palette_button_t **) list_next(cnt_btn);
    }

    for (; cnt < palette_btns_num; ++cnt)
    {
        (**cnt_btn).visible.enclosing = rectangle_t(
            visible.enclosing.ld_corner + r_column_off,
            visible.enclosing.ld_corner + r_column_off + palette_btn_size
        );

        r_column_off.y += palette_btn_size.y + 10;
        cnt_btn = (palette_button_t **) list_next(cnt_btn);
    }
}
