#include <stdio.h>
#include "label.h"

//==================================================================================================

#define label_data_init(string, char_size)                                                      \
text        (&font_t::get_font_by_name(font_t::EDU_QLD), string, color_t::Black, char_size),    \
text_rel_off(5, 5),                                                                             \
background  (color_t::White),                                                                   \
texture     ()

//==================================================================================================

label_t::label_t():
widget_t(),
label_data_init(nullptr, 30)
{}

//--------------------------------------------------------------------------------------------------

label_t::label_t(const rectangle_t &enclosing_):
widget_t(enclosing_),
label_data_init(nullptr, 30)
{}

//--------------------------------------------------------------------------------------------------

label_t::label_t(const char *string, const size_t char_size):
widget_t(),
label_data_init(string, char_size)
{}

//--------------------------------------------------------------------------------------------------

label_t::label_t(const rectangle_t &enclosing_, const char *string, const size_t char_size):
widget_t(enclosing_),
label_data_init(string, char_size)
{}

//--------------------------------------------------------------------------------------------------

void label_t::create_texture()
{
    render_texture_t temp((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);
    temp.clear(background);
    temp.draw_text(text, text_rel_off);

    temp.display();
    texture = temp.get_texture();
}
