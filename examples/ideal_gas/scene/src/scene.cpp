#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "scene.h"
#include "logs/log.h"

//==================================================================================================

static const vec2d REACTOR_LD_OFF(5, 5);
static const vec2d REACTOR_RU_OFF(5, 5);

//==================================================================================================

scene_t::scene_t(const vec2d &area_size_):
molecule_manager(6, 50, vec2d(area_size_.x / 2, area_size_.y) - (REACTOR_LD_OFF + REACTOR_RU_OFF)),

piston          (REACTOR_LD_OFF, vec2d(area_size_.x/2 - REACTOR_RU_OFF.x, REACTOR_LD_OFF.y)),
walls           (REACTOR_LD_OFF, vec2d(area_size_.x/2, area_size_.y) - REACTOR_RU_OFF)
{}

//--------------------------------------------------------------------------------------------------

void scene_t::draw(sf::RenderTarget &wnd)
{
    molecule_manager.draw();

    sf::Sprite molecule_spr(molecule_manager.get_texture());
    molecule_spr.setPosition((float) REACTOR_LD_OFF.x, (float) REACTOR_LD_OFF.y);

    wnd.draw(molecule_spr);

    draw_hollow_rectangle(walls, wnd, sf::Color::Green);
    draw_line(piston.endpoint_1, piston.endpoint_2 - piston.endpoint_1, wnd, sf::Color::Magenta);
}
