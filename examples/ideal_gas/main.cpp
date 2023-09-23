#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "scene.h"
#include "config.h"
#include "distance.h"

//==================================================================================================

static double get_frame_time();

//==================================================================================================

int main()
{
    rectangle_t walls(vec2d(5, 5), vec2d(400, 795));
    segment_t  piston(vec2d(5, 5), vec2d(400, 5));
    scene_t     scene(walls, 8, 50, piston, vec2d(0, 50));

    sf::RenderWindow wnd(sf::VideoMode(WND_WIDTH, WND_HEIGHT), WND_TITLE);
    while (wnd.isOpen())
    {
        sf::Event event;
        while (wnd.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wnd.close();
        }

        wnd.clear();

        scene.refresh(get_frame_time());
        scene.draw   (wnd);

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
