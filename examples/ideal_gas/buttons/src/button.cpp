#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "intersection.h"

#include "logs/log.h"
#include "algorithm/algorithm.h"

//==================================================================================================

button_t::button_t(const vec2d   &position_,
                   const vec2d   &size_,
                   const action_t action_,

                   const char *tex_on_file_,
                   const char *tex_off_file_):

area   (position_, position_ + size_),
scale  (1),
state  (BUTTON_OFF),
action (action_),
tex_on (),
tex_off()
{
    log_verify(dblcmp(position_.x, 0) >= 0, ;);
    log_verify(dblcmp(position_.y, 0) >= 0, ;);

    log_verify(dblcmp(size_.x, 0) >= 0, ;);
    log_verify(dblcmp(size_.y, 0) >= 0, ;);

    if (!tex_on .loadFromFile(tex_on_file_ )) { log_error("can't load texture from \"%s\"\n", tex_on_file_); }
    if (!tex_off.loadFromFile(tex_off_file_)) { log_error("can't load texture from \"%s\"\n", tex_off_file_); }

    sf::Vector2u size_on  = tex_on .getSize();
    sf::Vector2u size_off = tex_off.getSize();

    log_assert(size_on .x != 0); log_assert(size_on .y != 0);
    log_assert(size_off.x != 0); log_assert(size_off.y != 0);

    double scale_x = (size_on.x >= size_off.x) ? size_.x / size_on.x : size_.x / size_off.x;
    double scale_y = (size_on.y >= size_off.y) ? size_.y / size_on.y : size_.y / size_off.y;

    scale = vec2d(scale_x, scale_y);
}

//--------------------------------------------------------------------------------------------------

void button_t::draw(sf::RenderTarget &wnd) const
{
    const sf::Texture button_t::*cur_tex;
    switch (state)
    {
        case BUTTON_ON  :
        case BUTTON_HOLD: cur_tex = &button_t::tex_on;  break;
        case BUTTON_OFF : cur_tex = &button_t::tex_off; break;

        default: log_assert(false && "undefined BUTTON_STATE_TYPE\n");
    }

    sf::Sprite cur_spr (this->*cur_tex);
    cur_spr.setPosition((float) area.ld_corner.x, (float) area.ld_corner.y);
    cur_spr.setScale   ((float) scale.x         , (float) scale.y);

    wnd.draw(cur_spr);
}

//--------------------------------------------------------------------------------------------------

void button_t::refresh(const vec2d &mouse_pos, const bool is_clicked)
{
    if (!is_clicked)
    {
        state = BUTTON_OFF;
        return;
    }

    if (is_clicked && (state == BUTTON_ON || state == BUTTON_HOLD))
    {
        state = BUTTON_HOLD;
        return;
    }

    if (is_intersection_rectangle_point(area, mouse_pos))
        state = BUTTON_ON;
    else
        state = BUTTON_OFF;
}
