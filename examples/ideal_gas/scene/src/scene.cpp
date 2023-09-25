#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "scene.h"
#include "logs/log.h"

//==================================================================================================

scene_t::scene_t(const vec2d &area_size_):
molecule_manager(10, 100, vec2d(area_size_.x / 2, area_size_.y))
{}

//--------------------------------------------------------------------------------------------------

void scene_t::draw(sf::RenderTarget &wnd)
{
    molecule_manager.draw();

    sf::Sprite molecule_spr(molecule_manager.get_texture());
    molecule_spr.setPosition(0, 0);

    wnd.draw(molecule_spr);
}
