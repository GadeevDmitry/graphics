#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "intersection.h"

#include "logs/log.h"
#include "algorithm/algorithm.h"

//==================================================================================================

sf::Texture press_button_t::tex_on;
sf::Texture press_button_t::tex_off;
bool        press_button_t::are_texs_init = false;

//--------------------------------------------------------------------------------------------------

sf::Texture switch012_button_t::tex_0;
sf::Texture switch012_button_t::tex_1;
sf::Texture switch012_button_t::tex_2;
bool        switch012_button_t::are_texs_init = false;

//==================================================================================================

void press_button_t::texs_init()
{
    if (!tex_on .loadFromFile("../../widget/img/button_on.png" )) { log_assert(false && "can't load texture from file\n"); }
    if (!tex_off.loadFromFile("../../widget/img/button_off.png")) { log_assert(false && "can't load texture from file\n"); }

    are_texs_init = true;
}

//--------------------------------------------------------------------------------------------------

press_button_t::press_button_t(const vec2d    &pos_,
                               const vec2d    &size_,
                               const action_t &action_):
button_t(pos_, size_),
state   (BUTTON_OFF),
action  (action_),
scale   (1, 1)
{
    log_verify(dblcmp(pos_.x , 0) >= 0, ;);
    log_verify(dblcmp(pos_.y , 0) >= 0, ;);
    log_verify(dblcmp(size_.x, 0) >= 0, ;);
    log_verify(dblcmp(size_.y, 0) >= 0, ;);

    if (!are_texs_init) texs_init();

    sf::Vector2u size_on  = tex_on .getSize();
    sf::Vector2u size_off = tex_off.getSize();

    log_assert(size_on .x != 0); log_assert(size_on .y != 0);
    log_assert(size_off.x != 0); log_assert(size_off.y != 0);

    double scale_x = (size_on.x >= size_off.x) ? size_.x / size_on.x : size_.x / size_off.x;
    double scale_y = (size_on.y >= size_off.y) ? size_.y / size_on.y : size_.y / size_off.y;

    scale = vec2d(scale_x, scale_y);
}

//--------------------------------------------------------------------------------------------------

void press_button_t::draw(sf::RenderTarget &wnd) const
{
    sf::Texture *cur_tex = nullptr;
    switch (state)
    {
        case BUTTON_PRESS  :
        case BUTTON_HOLD   : cur_tex = &press_button_t::tex_on; break;
        case BUTTON_OFF    :
        case BUTTON_RELEASE: cur_tex = &press_button_t::tex_off; break;

        default: log_assert(false && "undefined press_button_t::BUTTON_STATE_TYPE\n");
    }

    sf::Sprite cur_spr (*cur_tex);
    cur_spr.setPosition((float) area.ld_corner.x, (float) area.ld_corner.y);
    cur_spr.setScale   ((float) scale.x         , (float) scale.y);

    wnd.draw(cur_spr);
}

//--------------------------------------------------------------------------------------------------

void press_button_t::refresh(const vec2d &mouse_pos, const bool is_clicked)
{
    if (!is_clicked)
    {
        switch (state)
        {
            case BUTTON_PRESS  :
            case BUTTON_HOLD   : state = BUTTON_RELEASE; break;
            case BUTTON_OFF    :
            case BUTTON_RELEASE: state = BUTTON_OFF; break;

            default: log_assert(false && "undefined press_button_t::BUTTON_STATE_TYPE\n");
        }
    }
    else
    {
        switch (state)
        {
            case BUTTON_PRESS  :
            case BUTTON_HOLD   : state = BUTTON_HOLD; break;
            case BUTTON_OFF    :
            case BUTTON_RELEASE: state = is_intersection_rectangle_point(area, mouse_pos) ? BUTTON_PRESS : BUTTON_OFF;
                                 break;

            default: log_assert(false && "undefined press_button_t::BUTTON_STATE_TYPE\n");
        }
    }
}

//--------------------------------------------------------------------------------------------------

void switch012_button_t::texs_init()
{
    if (!tex_0.loadFromFile("../../widget/img/switch012_0.png")) { log_assert("can't load texture from file\n"); }
    if (!tex_1.loadFromFile("../../widget/img/switch012_1.png")) { log_assert("can't load texture from file\n"); }
    if (!tex_2.loadFromFile("../../widget/img/switch012_2.png")) { log_assert("can't load texture from file\n"); }

    are_texs_init = true;
}

//--------------------------------------------------------------------------------------------------

switch012_button_t::switch012_button_t(const vec2d &pos_,
                                       const vec2d &size_,
                                       const action_t &action_0_,
                                       const action_t &action_1_,
                                       const action_t &action_2_):
button_t(pos_, size_),
state   (BUTTON_RELEASE_0),
action_0(action_0_),
action_1(action_1_),
action_2(action_2_),
scale   (1, 1)
{
    log_verify(dblcmp(pos_.x , 0) >= 0, ;);
    log_verify(dblcmp(pos_.y , 0) >= 0, ;);
    log_verify(dblcmp(size_.x, 0) >= 0, ;);
    log_verify(dblcmp(size_.y, 0) >= 0, ;);

    if (!are_texs_init) texs_init();

    sf::Vector2u size_0 = tex_0.getSize();
    sf::Vector2u size_1 = tex_1.getSize();
    sf::Vector2u size_2 = tex_2.getSize();

    log_assert(size_0.x != 0); log_assert(size_0.y != 0);
    log_assert(size_1.x != 0); log_assert(size_1.y != 0);
    log_assert(size_2.x != 0); log_assert(size_2.y != 0);

    double scale_x = size_.x / std::max({size_0.x, size_1.x, size_2.x});
    double scale_y = size_.y / std::max({size_0.y, size_1.y, size_2.y});

    scale = vec2d(scale_x, scale_y);
}

//--------------------------------------------------------------------------------------------------

void switch012_button_t::draw(sf::RenderTarget &wnd) const
{
    sf::Texture *cur_tex = nullptr;
    switch (state)
    {
        case BUTTON_HOLD_0:
        case BUTTON_RELEASE_0:
        case BUTTON_SWITCHED_TO_0: cur_tex = &switch012_button_t::tex_0; break;

        case BUTTON_HOLD_1:
        case BUTTON_RELEASE_1:
        case BUTTON_SWITCHED_TO_1: cur_tex = &switch012_button_t::tex_1; break;

        case BUTTON_HOLD_2:
        case BUTTON_RELEASE_2:
        case BUTTON_SWITCHED_TO_2: cur_tex = &switch012_button_t::tex_2; break;

        default: log_assert(false && "undefined switch012_button_t::BUTTON_STATE_TYPE\n");
    }

    sf::Sprite cur_spr (*cur_tex);
    cur_spr.setPosition((float) area.ld_corner.x, (float) area.ld_corner.y);
    cur_spr.setScale   ((float) scale.x         , (float) scale.y);

    wnd.draw(cur_spr);
}

//--------------------------------------------------------------------------------------------------

void switch012_button_t::refresh(const vec2d &mouse_pos, const bool is_clicked)
{
    if (!is_clicked)
    {
        switch (state)
        {
            case BUTTON_HOLD_0:
            case BUTTON_SWITCHED_TO_0: state = BUTTON_RELEASE_0; break;

            case BUTTON_HOLD_1:
            case BUTTON_SWITCHED_TO_1: state = BUTTON_RELEASE_1; break;

            case BUTTON_HOLD_2:
            case BUTTON_SWITCHED_TO_2: state = BUTTON_RELEASE_2; break;

            case BUTTON_RELEASE_0:
            case BUTTON_RELEASE_1:
            case BUTTON_RELEASE_2: break;

            default: log_assert(false && "undefined switch012_button_t::BUTTON_STATE_TYPE\n");
        }
    }
    else
    {
        vec2d section_width (area.ru_corner.x - area.ld_corner.x, 0);
        vec2d section_height(0, (area.ru_corner.y - area.ld_corner.y) / 3);

        static rectangle_t section_0(area.ld_corner, area.ld_corner + section_width + section_height);
        static rectangle_t section_1(area.ld_corner + section_height, area.ru_corner - section_height);
        static rectangle_t section_2(area.ru_corner - section_height - section_width, area.ru_corner);

        switch (state)
        {
            case BUTTON_SWITCHED_TO_0: state = BUTTON_HOLD_0; break;
            case BUTTON_SWITCHED_TO_1: state = BUTTON_HOLD_1; break;
            case BUTTON_SWITCHED_TO_2: state = BUTTON_HOLD_2; break;

            case BUTTON_HOLD_0:
            case BUTTON_HOLD_1:
            case BUTTON_HOLD_2: break;

            case BUTTON_RELEASE_0:
            case BUTTON_RELEASE_1:
            case BUTTON_RELEASE_2:
            {
                if (is_intersection_rectangle_point(section_0, mouse_pos)) state = (state == BUTTON_RELEASE_0) ? BUTTON_HOLD_0 : BUTTON_SWITCHED_TO_0;
                if (is_intersection_rectangle_point(section_1, mouse_pos)) state = (state == BUTTON_RELEASE_1) ? BUTTON_HOLD_1 : BUTTON_SWITCHED_TO_1;
                if (is_intersection_rectangle_point(section_2, mouse_pos)) state = (state == BUTTON_RELEASE_2) ? BUTTON_HOLD_2 : BUTTON_SWITCHED_TO_2;

                break;
            }

            default: log_assert(false && "undefined switch012_button_t::BUTTON_STATE_TYPE\n");
        }
    }
}
