#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "application.h"

//==================================================================================================

//static const vec2d MAIN_WINDOW_SIZE(1920, 1080);

//==================================================================================================

int main()
{
    application_t::load_textures();
    application_t::load_fonts();

    sf::RenderWindow sfml_wnd(sf::VideoMode(), "graphic editor", sf::Style::Fullscreen);
    render_texture_t rend_texture(sfml_wnd.getSize().x, sfml_wnd.getSize().y);

    application_t app(vec2d((double) sfml_wnd.getSize().x, (double) sfml_wnd.getSize().y));
    app.process(sfml_wnd, rend_texture);
}
