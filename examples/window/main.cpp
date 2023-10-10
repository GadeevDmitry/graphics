#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "log.h"
#include "window.h"
#include "window_manager.h"

//==================================================================================================
/*
const double COL_WND_SCALE = 0.8;
const char  *SFML_WND_NAME = "simple window";

void init(const sf::RenderWindow &sfml_wnd, color_window_t &col_wnd, render_texture_t &rend_texture);
void run (      sf::RenderWindow &sfml_wnd, color_window_t &col_wnd, render_texture_t &rend_texture);
*/
//==================================================================================================

int main()
{
    sf::RenderWindow sfml_wnd(sf::VideoMode(), "simple", sf::Style::Fullscreen);
    render_texture_t rend_texture(sfml_wnd.getSize().x, sfml_wnd.getSize().y);

    color_window_t wnd_1(rectangle_t(vec2d(100 , 200), vec2d(1400, 900)), color_t::Orange);
    color_window_t wnd_2(rectangle_t(vec2d(100 , 200), vec2d(300 , 250)), color_t::Green);
    color_window_t wnd_3(rectangle_t(vec2d(600 , 100), vec2d(800 , 350)), color_t::Blue);
    color_window_t wnd_4(rectangle_t(vec2d(400 , 500), vec2d(500 , 700)), color_t::Red);
    color_window_t wnd_5(rectangle_t(vec2d(700 , 500), vec2d(900 , 700)), color_t::White);
    color_window_t wnd_6(rectangle_t(vec2d(1200, 300), vec2d(1600, 400)), color_t::Black);

    wnd_1.visible -= wnd_2.visible;
    wnd_1.visible -= wnd_3.visible;
    wnd_1.visible -= wnd_4.visible;
    wnd_1.visible -= wnd_5.visible;
    wnd_1.visible -= wnd_6.visible;

    wnd_1.render(rend_texture);
    wnd_2.render(rend_texture);
    wnd_3.render(rend_texture);
    wnd_4.render(rend_texture);
    wnd_5.render(rend_texture);
    wnd_6.render(rend_texture);

    wnd_1.visible.render(rend_texture);

    sf::Sprite spr(rend_texture.get_sfml_texture());
    sfml_wnd.draw(spr);
    sfml_wnd.display();

    while (sfml_wnd.isOpen())
    {
        sf::Event event;
        while (sfml_wnd.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                sfml_wnd.close();
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
/*
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
                        col_wnd.on_key_press(widget_t::key_t(event.key.code));
                    break;
                }
                case sf::Event::KeyReleased:
                {
                    col_wnd.on_key_release(widget_t::key_t(event.key.code));
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    col_wnd.on_mouse_press(widget_t::mouse_context_t(event.mouseButton.button, sf::Mouse::getPosition()));
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    col_wnd.on_mouse_release(widget_t::mouse_context_t(event.mouseButton.button, sf::Mouse::getPosition()));
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
*/
