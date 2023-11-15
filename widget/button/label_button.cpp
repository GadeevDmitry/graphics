#include <stdio.h>
#include "button/label_button.h"

//==================================================================================================

#define label_button_data_init(btn_name, char_size)                                             \
text        (&font_t::get_font_by_name(font_t::EDU_QLD), btn_name, color_t::Black, char_size),  \
text_rel_off(5, 5),                                                                             \
background  (color_t::White),                                                                   \
border_color(color_t::Black),                                                                   \
texture     ()

//==================================================================================================

label_button_t::label_button_t(widget_controller_t &controller_):
button_t(controller_),
label_button_data_init(nullptr, 20)
{}

//--------------------------------------------------------------------------------------------------

label_button_t::label_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_):
button_t(controller_, enclosing_),
label_button_data_init(nullptr, 20)
{}

//--------------------------------------------------------------------------------------------------

label_button_t::label_button_t(widget_controller_t &controller_, const char *btn_name, const size_t char_size):
button_t(controller_),
label_button_data_init(btn_name, char_size)
{}

//--------------------------------------------------------------------------------------------------

label_button_t::label_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const char *btn_name, const size_t char_size):
button_t(controller_, enclosing_),
label_button_data_init(btn_name, char_size)
{}

//--------------------------------------------------------------------------------------------------

void label_button_t::create_texture()
{
    render_texture_t temp((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);
    temp.draw_rectangle(rectangle_t(vec2d(1, 1), enclosing.get_size() - vec2d(1, 1)), background, border_color, 1);
    temp.draw_text(text, text_rel_off);

    temp.display();
    texture = temp.get_texture();
}
