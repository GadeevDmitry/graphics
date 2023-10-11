#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "log.h"
#include "window.h"
#include "window_manager.h"

//==================================================================================================

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos);
static void         widgets_dump    (const list &widgets);

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

    vec2d wnd_size((double) sfml_wnd.getSize().x, (double) sfml_wnd.getSize().y);
    window_manager_t manager(nullptr, rectangle_t(vec2d(0, 0), wnd_size));

    color_window_t wnd_1(rectangle_t(vec2d(100, 200), vec2d(1400, 900)), color_t::White);
    color_window_t wnd_2(rectangle_t(vec2d(400, 500), vec2d(1000, 800)), color_t::Blue);

    manager.register_window(&wnd_1);
    manager.register_window(&wnd_2);

    manager.recalc_region(vec2d(0,0));
    manager.render(rend_texture);

//  LOG_TAB_SERVICE_MESSAGE("after recalc", "\n");
//  const list &widgets = manager.get_widgets();
//  widgets_dump(widgets);
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
                sfml_wnd.close();
        }
    }
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wswitch-default"

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
                    manager.on_mouse_press(widget_t::refresh_mouse_context(event.mouseButton.button,
                                       recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition(sfml_wnd))));
                    manager.recalc_region(vec2d(0, 0));
                } break;

                case sf::Event::MouseButtonReleased:
                {
                    manager.on_mouse_release(widget_t::refresh_mouse_context(event.mouseButton.button,
                                         recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition(sfml_wnd))));
                    manager.recalc_region(vec2d(0, 0));
                } break;

                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mouse_pos = recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition(sfml_wnd));
                    vec2d        move_vec  = vec2d((double) mouse_pos.x, (double) mouse_pos.y) -
                                             widget_t::get_mouse_context().pos;

                    widget_t::mouse_context_t move_context(move_vec, widget_t::get_mouse_context().btn);
                    widget_t::refresh_mouse_pos(mouse_pos);

                    manager.on_mouse_move(move_context);
                    manager.recalc_region(vec2d(0, 0));
                } break;
            }

            sfml_wnd.clear();
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
    return sf::Vector2i(mouse_pos.x, sfml_wnd.getSize().y - mouse_pos.y);
}

//--------------------------------------------------------------------------------------------------

static void widgets_dump(const list &widgets)
{
    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);

    for (widget_t **cur = front; cur != fict;
         cur = (widget_t **) list_next(cur))
    {
        LOG_TAB_SERVICE_MESSAGE("\nwidget region", "\n");

        clipping_region_t &reg = (**cur).get_clipping_region();
        clipping_region_t::dump(&reg);
    }
}
