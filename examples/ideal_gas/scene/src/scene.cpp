#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "scene.h"
#include "logs/log.h"

//==================================================================================================

scene_t::scene_t(const vec2d &area_size_):
molecule_manager(10, 100, vec2d(area_size_.x / 2, area_size_.y)),
reactor_offset  (0, 0),

button_manager(vec2d(area_size_.x / 4, area_size_.y / 4)),
board_offset  (area_size_.x / 2, 0)
{}

//--------------------------------------------------------------------------------------------------

void scene_t::draw(sf::RenderTarget &wnd)
{
    molecule_manager.draw();
    sf::Sprite molecule_spr(molecule_manager.get_texture());
    molecule_spr.setPosition((float) reactor_offset.x, (float) reactor_offset.y);
    wnd.draw(molecule_spr);

    button_manager.draw();
    sf::Sprite button_spr(button_manager.get_texture());
    button_spr.setPosition((float) board_offset.x, (float) board_offset.y);
    wnd.draw(button_spr);
}
