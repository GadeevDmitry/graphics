#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "log.h"
#include "window.h"
#include "window_manager.h"

//==================================================================================================

const vec2d MAIN_WINDOW_SIZE(1920, 1080);

//==================================================================================================

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos);

static void         render          (sf::RenderWindow &sfml_wnd, widget_t &system, render_texture_t &rend_texture);
static void         load_textures   ();

//==================================================================================================

int main()
{
    load_textures();

    sf::RenderWindow sfml_wnd(sf::VideoMode(), "simple", sf::Style::Fullscreen);
    vec2d            sfml_wnd_size((double) sfml_wnd.getSize().x, (double) sfml_wnd.getSize().y);

    render_texture_t rend_texture((unsigned) sfml_wnd_size.x, (unsigned) sfml_wnd_size.y);
    window_manager_t manager     (nullptr, rectangle_t(vec2d(0, 0), sfml_wnd_size));

    main_window_t wnd_1(rectangle_t(vec2d(0  ,   0), MAIN_WINDOW_SIZE));
    window_t      wnd_2(rectangle_t(vec2d(400, 500), vec2d(1000, 800)), window_t::Light_theme);
    window_t      wnd_3(rectangle_t(vec2d(200, 300), vec2d(800 ,1000)), window_t::Dark_theme);

    wnd_1.register_subwindow(&wnd_2);
    wnd_1.register_subwindow(&wnd_3);

    manager.register_window(&wnd_1);
    manager.init();

    render(sfml_wnd, manager, rend_texture);
/*
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

            bool rerender = false;

            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                {
                    LOG_TAB_MESSAGE("MOUSE_BUTTON_PRESSED: {%lu, %lu}\n", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    LOG_TAB++;
                    rerender = widget_t::process_mouse_press_event
                                    (manager, mouse_context_t::convert_sfml(event.mouseButton.button));
                    LOG_TAB--;
                } break;

                case sf::Event::MouseButtonReleased:
                {
                    LOG_TAB_MESSAGE("MOUSE_BUTTON_RELEASED: {%lu, %lu}\n", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    LOG_TAB++;
                    rerender = widget_t::process_mouse_release_event
                                    (manager, mouse_context_t::convert_sfml(event.mouseButton.button));
                    LOG_TAB--;
                } break;

                case sf::Event::MouseMoved:
                {
                    rerender = widget_t::process_mouse_move_event
                                    (manager, recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition()));
                } break;

                default: break;
            }

            if (!rerender) continue;
            render(sfml_wnd, manager, rend_texture);
        }
    }
#pragma GCC diagnostic pop
}

//--------------------------------------------------------------------------------------------------

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos)
{
    return mouse_pos;
    return sf::Vector2i(mouse_pos.x, (int) sfml_wnd.getSize().y - mouse_pos.y);
}

//--------------------------------------------------------------------------------------------------

static void render(sf::RenderWindow &sfml_wnd, widget_t &system, render_texture_t &rend_texture)
{
    system.render(rend_texture);
    rend_texture.display();

    sf::Sprite spr(rend_texture.get_sfml_texture());
    sfml_wnd.draw(spr);
    sfml_wnd.display();
}

//--------------------------------------------------------------------------------------------------

static void load_textures()
{
    button_t::load_textures();
}
