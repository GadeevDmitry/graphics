#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "intersection.h"

#include "logs/log.h"

//==================================================================================================

void button_t::draw(sf::RenderWindow &wnd)
{
    sf::Texture cur_tex;

    switch (state)
    {
        case BUTTON_ON : cur_tex = tex_on;  break;
        case BUTTON_OFF: cur_tex = tex_off; break;

        default: log_assert(false && "undefined BUTTON_STATE_TYPE\n");
    }

    sf::Sprite spr(cur_tex);
    spr.setPosition(shape.ld_corner.x, shape.ld_corner.y);
    spr.setScale(scale.x, scale.y);

    wnd.draw(spr);
}

//--------------------------------------------------------------------------------------------------

void button_t::refresh(const vec2d &mouse_pos, const bool is_clicked)
{
    if (!is_clicked)
    {
        state = BUTTON_OFF;
        return;
    }

    if (is_intersection_rectangle_point(shape, mouse_pos))
        state = BUTTON_ON;
    else
        state = BUTTON_OFF;
}

//--------------------------------------------------------------------------------------------------


