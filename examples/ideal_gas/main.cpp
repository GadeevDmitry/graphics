#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "molecule.h"
#include "segment.h"
#include "gas_scene.h"
#include "material_point.h"

//==================================================================================================

static double get_frame_time();

//==================================================================================================

int main()
{
    rectangle_t vessel(vec2d(5, 5), vec2d(400, 795));
    piston_t    piston(material_point_t(vec2d(200, 0), vec2d(0, 0)), segment_t(vec2d(5, 5), vec2d(400, 5)));
    gas_scene_t scene (piston, vessel);

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
