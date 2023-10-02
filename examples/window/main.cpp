#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "log.h"
#include "window.h"

//==================================================================================================

const double COL_WND_SCALE = 0.8;
const char  *SFML_WND_NAME = "simple window";

void init(const sf::RenderWindow &sfml_wnd, color_window_t &col_wnd, render_texture_t &rend_texture);
void run (      sf::RenderWindow &sfml_wnd, color_window_t &col_wnd, render_texture_t &rend_texture);

//==================================================================================================

int main()
{
    sf::RenderWindow sfml_wnd(sf::VideoMode(), SFML_WND_NAME, sf::Style::Fullscreen);
    color_window_t   col_wnd;
    render_texture_t rend_texture;

    init(sfml_wnd, col_wnd, rend_texture);
    run (sfml_wnd, col_wnd, rend_texture);
}

//--------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"

void run(sf::RenderWindow &sfml_wnd, color_window_t &col_wnd, render_texture_t &rend_texture)
{
    while (sfml_wnd.isOpen())
    {
        sf::Event event;
        while (sfml_wnd.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    sfml_wnd.close();
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Escape)
                        sfml_wnd.close();
                    else
                        col_wnd.on_key_press(widget_t::convert_key(event.key.code));
                    break;
                }
                case sf::Event::KeyReleased:
                {
                    col_wnd.on_key_release(widget_t::convert_key(event.key.code));
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    MOUSE_BUTTON_TYPE btn = widget_t::convert_mouse_btn(event.mouseButton.button);
                    vec2d             pos((double) event.mouseButton.x, (double) event.mouseButton.y);
                    col_wnd.on_mouse_press(pos, btn);
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    MOUSE_BUTTON_TYPE btn = widget_t::convert_mouse_btn(event.mouseButton.button);
                    vec2d             pos((double) event.mouseButton.x, (double) event.mouseButton.y);
                    col_wnd.on_mouse_release(pos, btn);
                    break;
                }

                default: break;
            }
        }
        sfml_wnd    .clear();
        rend_texture.clear();

        col_wnd.render(rend_texture);

        sf::Sprite spr(rend_texture.get_sfml_texture());
        sfml_wnd.draw (spr);
        sfml_wnd.display();
    }
}

#pragma GCC diagnostic pop

//--------------------------------------------------------------------------------------------------

void init(const sf::RenderWindow &sfml_wnd, color_window_t &col_wnd, render_texture_t &rend_texture)
{
    LOG_ASSERT(dblcmp(COL_WND_SCALE, 1.0) <= 0);

    vec2d sfml_wnd_size((double) sfml_wnd.getSize().x, (double) sfml_wnd.getSize().y);
    vec2d col_wnd_size = COL_WND_SCALE * sfml_wnd_size;

    vec2d ld_corner = (sfml_wnd_size - col_wnd_size) / 2;
    vec2d ru_corner = ld_corner + col_wnd_size;

    col_wnd.set_area(rectangle_t(ld_corner, ru_corner));
    col_wnd.color = color_t::Orange;

    rend_texture.create((unsigned) sfml_wnd_size.x, (unsigned) sfml_wnd_size.y);
}

