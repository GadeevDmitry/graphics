#include <stdio.h>
#include "button/color_button.h"

//==================================================================================================

#define color_button_data_init(border_, background_)    \
border    (border_),                                    \
background(background_),                                \
texture   ()

//==================================================================================================

color_button_t::color_button_t(widget_controller_t &controller_):
button_t(controller_),
color_button_data_init(color_t::Black, color_t::White)
{}

//--------------------------------------------------------------------------------------------------

color_button_t::color_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_):
button_t(controller_, enclosing_),
color_button_data_init(color_t::Black, color_t::White)
{}

//--------------------------------------------------------------------------------------------------

color_button_t::color_button_t(widget_controller_t &controller_, const color_t &border_, const color_t &background_):
button_t(controller_),
color_button_data_init(border_, background_)
{}

//--------------------------------------------------------------------------------------------------

color_button_t::color_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const color_t &border_, const color_t &background_):
button_t(controller_),
color_button_data_init(border_, background_)
{}

//--------------------------------------------------------------------------------------------------

void color_button_t::create_texture()
{
    render_texture_t temp((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);
    temp.draw_rectangle(rectangle_t(vec2d(1, 1), enclosing.get_size() - vec2d(1, 1)), background, border, 1);

    temp.display();
    texture = temp.get_texture();
}
