#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "config.h"

#include "color.h"
#include "lighter.h"
#include "material.h"
#include "render_body.h"
#include "render_sphere.h"
#include "raytracer.h"
#include "vec3d.h"

//==================================================================================================

static void raytracer_init(raytracer_t &raytracer);
static void render(sf::RenderWindow &wnd, const raytracer_t &raytracer);

//==================================================================================================

int main()
{
    raytracer_t raytracer(color_t(0.1, 0.1, 0.1), vec3d(0, 0, 300));
    raytracer_init(raytracer);

    sf::RenderWindow wnd(sf::VideoMode(WND_WIDTH, WND_HEIGHT), WND_TITLE);
    render(wnd, raytracer);
    wnd.display();

    while (wnd.isOpen())
    {
        sf::Event event;
        while (wnd.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wnd.close();
        }
    }
}

//--------------------------------------------------------------------------------------------------

static void raytracer_init(raytracer_t &raytracer)
{
    static render_sphere_t sphere_1(material_t(material_t::Plastic, color_t::Red   ), vec3d(-300, 0, -300), 200);
    static render_sphere_t sphere_2(material_t(material_t::Plastic, color_t::Orange), vec3d(-100, 0, -100), 100);
    static render_sphere_t sphere_3(material_t(material_t::Plastic, color_t::Green ), vec3d( 200, 0, -600), 400);
    static render_sphere_t sphere_4(material_t(material_t::Plastic, color_t::Blue  ), vec3d( 200, 0,    0), 100);

    static lighter_t lighter_1(color_t::White, vec3d( 200, 100, 50));
    static lighter_t lighter_2(color_t::White, vec3d(-300,   0,  0));

    raytracer.scene.add_lighter(&lighter_1);
    raytracer.scene.add_lighter(&lighter_2);

    raytracer.scene.add_render_body(&sphere_1);
    raytracer.scene.add_render_body(&sphere_2);
    raytracer.scene.add_render_body(&sphere_3);
    raytracer.scene.add_render_body(&sphere_4);
}

//--------------------------------------------------------------------------------------------------

static void render(sf::RenderWindow &wnd, const raytracer_t &raytracer)
{
    for (int wnd_x = 0; wnd_x < (int) WND_WIDTH ; ++wnd_x) {
    for (int wnd_y = 0; wnd_y < (int) WND_HEIGHT; ++wnd_y)
        {
            color_t pixel_color = raytracer.raytrace(WND_BEGIN_PT + vec3d(wnd_x, -wnd_y, 0), 1);

            sf::Uint8 real_r = (sf::Uint8) ((pixel_color.r > 1) ? 255 : pixel_color.r * 255);
            sf::Uint8 real_g = (sf::Uint8) ((pixel_color.g > 1) ? 255 : pixel_color.g * 255);
            sf::Uint8 real_b = (sf::Uint8) ((pixel_color.b > 1) ? 255 : pixel_color.b * 255);

            sf::RectangleShape pixel_image(sf::Vector2f(1, 1));
            pixel_image.setFillColor(sf::Color(real_r, real_g, real_b));
            pixel_image.setPosition (sf::Vector2f(wnd_x, wnd_y));

            wnd.draw(pixel_image);
        }
    }
}
