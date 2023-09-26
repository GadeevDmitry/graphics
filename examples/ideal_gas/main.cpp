#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "scene.h"
#include "config.h"

//==================================================================================================

static double get_frame_time();

//==================================================================================================

int main()
{
    sf::RenderWindow  wnd(sf::VideoMode(WND_WIDTH, WND_HEIGHT), WND_TITLE);
    scene_t scene(vec2d(WND_WIDTH, WND_HEIGHT));

    while (wnd.isOpen())
    {
        sf::Event event;
        while (wnd.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wnd.close();
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(wnd);
        bool        is_clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        wnd.clear();
        scene.refresh(get_frame_time(), vec2d(mouse_pos.x, mouse_pos.y), is_clicked);
        scene.draw(wnd);
        wnd.display();
    }
}

//--------------------------------------------------------------------------------------------------

static double get_frame_time()
{
    static clock_t start = clock();

    clock_t finish    = clock();
    double frame_time = (double) (finish - start) / CLOCKS_PER_SEC;

    start = clock();
    return frame_time;
}
