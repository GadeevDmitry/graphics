#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "coord_system.h"
#include <draw.h>

int main()
{
    coord_system sys(400, 400, 50, 50);

    vec simple = vec(1, 1);
    vec rotate = vec(1, 1);

    sf::RenderWindow wnd(sf::VideoMode(WND_WIDTH, WND_HEIGHT), WND_TITLE);
    while (wnd.isOpen())
    {
        sf::Event event;
        while (wnd.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wnd.close();
        }

        rotate ^= 10;

        wnd.clear();

        draw_coord_sys(             sys, wnd, sf::Color::White);
        draw_vec(vec(0, 0), simple, sys, wnd, sf::Color::Green);
        draw_vec(simple   , rotate, sys, wnd, sf::Color::Red);

        wnd.display();

        sleep(1);
    }
}
