#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "coord_system.h"
#include "draw.h"

//==================================================================================================

static void rotate_vec(vec2d &rot);
static void mouse_vec(const vec2d &vec_mouse_beg, vec2d &vec_mouse_main, const coord_system &sys, const sf::RenderWindow &wnd);

//==================================================================================================

int main()
{
    coord_system sys(400, 400, 50, 50);

    vec2d simple(1, 1);
    vec2d rotate(5, 3);
    vec2d mouse (4, 6);

    sf::RenderWindow wnd(sf::VideoMode(WND_WIDTH, WND_HEIGHT), WND_TITLE);

    while (wnd.isOpen())
    {
        sf::Event event;
        while (wnd.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wnd.close();
        }

        rotate_vec(rotate);
        mouse_vec (rotate + simple, mouse, sys, wnd);

        wnd.clear();

        draw_coord_sys(                     sys, wnd, sf::Color::White);
        draw_vec2d(vec2d(0, 0)    , simple, sys, wnd, sf::Color::Green);
        draw_vec2d(simple         , rotate, sys, wnd, sf::Color::Red);
        draw_vec2d(rotate + simple, mouse , sys, wnd, sf::Color::Blue);

        wnd.display();
    }
}

//--------------------------------------------------------------------------------------------------

static void rotate_vec(vec2d &rot)
{
    static clock_t start = clock();

    clock_t finish = clock();
    rot.rotate(double (360) * (finish - start) / (3 * CLOCKS_PER_SEC));
    start = clock();
}

//--------------------------------------------------------------------------------------------------

static void mouse_vec(const vec2d &vec_mouse_beg, vec2d &vec_mouse_main, const coord_system &sys, const sf::RenderWindow &wnd)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(wnd);

    vec2d mouse_coord = sys.get_rel_from_off(vec2d(mouse_pos.x, mouse_pos.y));
    vec_mouse_main    = (mouse_coord - vec_mouse_beg).get_normalization(vec_mouse_main.len());
}
