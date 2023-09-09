#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "coord_system.h"
#include <draw.h>

static void rotate_vec(vec &rot);
static void mouse_vec(const vec &vec_mouse_beg, vec &vec_mouse_main, const coord_system &sys, const sf::RenderWindow &wnd);

int main()
{
    coord_system sys(400, 400, 50, 50);

    vec simple = vec(1, 1);
    vec rotate = vec(5, 3);
    vec mouse  = vec(4, 6);

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

        draw_coord_sys(                   sys, wnd, sf::Color::White);
        draw_vec(vec(0, 0)      , simple, sys, wnd, sf::Color::Green);
        draw_vec(simple         , rotate, sys, wnd, sf::Color::Red);
        draw_vec(rotate + simple, mouse , sys, wnd, sf::Color::Blue);

        wnd.display();
    }
}

static void rotate_vec(vec &rot)
{
    static clock_t start = clock();

    clock_t finish = clock();
    rot ^= double (360) * (finish - start) / (3 * CLOCKS_PER_SEC);
    start = clock();
}

static void mouse_vec(const vec &vec_mouse_beg, vec &vec_mouse_main, const coord_system &sys, const sf::RenderWindow &wnd)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(wnd);

    vec mouse_coord = sys.get_vec_from_pixel(vec(mouse_pos.x, mouse_pos.y));
    vec_mouse_main  = (mouse_coord - vec_mouse_beg) | ~vec_mouse_main;
}
