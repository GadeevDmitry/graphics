#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "log.h"
#include "window.h"
#include "window_manager.h"

//==================================================================================================

int main()
{
    sf::RenderWindow sfml_wnd(sf::VideoMode(), "simple", sf::Style::Fullscreen);
    render_texture_t rend_texture(sfml_wnd.getSize().x, sfml_wnd.getSize().y);
/*
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
*/

    color_window_t wnd(rectangle_t(vec2d(100, 200), vec2d(1400, 900)));
    wnd.render(rend_texture);

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
