#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "log.h"
#include "window.h"
#include "window_manager.h"

//==================================================================================================

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos);

//==================================================================================================

int main()
{
    sf::RenderWindow sfml_wnd(sf::VideoMode(), "simple", sf::Style::Fullscreen);

    render_texture_t rend_texture(sfml_wnd.getSize().x, sfml_wnd.getSize().y);
    window_manager_t manager     (nullptr, rectangle_t(vec2d(0, 0), vec2d((double) sfml_wnd.getSize().x, (double) sfml_wnd.getSize().y)));

    color_window_t wnd_1(rectangle_t(vec2d(100, 200), vec2d(1400, 900)), color_t::White);
    color_window_t wnd_2(rectangle_t(vec2d(400, 500), vec2d(1000, 800)), color_t::Green);
    color_window_t wnd_3(rectangle_t(vec2d(200, 300), vec2d(800 ,1000)), color_t::Red);

    manager.register_window(&wnd_1);
    manager.register_window(&wnd_2);
    manager.register_window(&wnd_3);
    manager.recalc_region  ();
/*
    sfml_wnd    .clear(sf::Color::Cyan);
    rend_texture.clear();

    manager.render(rend_texture);

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

    return 0;
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wswitch-enum"

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

            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                {
                    LOG_TAB_SERVICE_MESSAGE("MOUSE BUTTON PRESSED {%u, %u}", "\n",
                    sf::Mouse::getPosition().x,
                    sf::Mouse::getPosition().y);
                    LOG_TAB++;

                    widget_t::process_mouse_press_event
                        (manager, mouse_context_t::convert_sfml(event.mouseButton.button));

                    LOG_TAB--;
                } break;

                case sf::Event::MouseButtonReleased:
                {
                    LOG_TAB_SERVICE_MESSAGE("MOUSE BUTTON RELEASED", "\n");
                    LOG_TAB++;

                    widget_t::process_mouse_release_event
                        (manager, mouse_context_t::convert_sfml(event.mouseButton.button));

                    LOG_TAB--;
                } break;

                case sf::Event::MouseMoved:
                {
                    widget_t::process_mouse_move_event
                        (manager, recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition()));
                } break;

                default: break;
            }

            sfml_wnd    .clear(sf::Color::Cyan);
            rend_texture.clear();

            manager.render(rend_texture);

            sf::Sprite spr(rend_texture.get_sfml_texture());
            sfml_wnd.draw(spr);
            sfml_wnd.display();
        }
    }

#pragma GCC diagnostic pop
}

//--------------------------------------------------------------------------------------------------

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos)
{
    return sf::Vector2i(mouse_pos.x, (int) sfml_wnd.getSize().y - mouse_pos.y);
}
