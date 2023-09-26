#include <stdio.h>
#include <stdlib.h>

#include "button.h"
#include "intersection.h"

#include "logs/log.h"
#include "algorithm/algorithm.h"

//==================================================================================================

sf::Texture hold_button_t::tex_on;
sf::Texture hold_button_t::tex_off;

//--------------------------------------------------------------------------------------------------

sf::Texture switch012_button_t::tex_0;
sf::Texture switch012_button_t::tex_1;
sf::Texture switch012_button_t::tex_2;

//==================================================================================================

void hold_button_t::texs_init()
{
    if (!tex_on .loadFromFile("../../widget/img/button_on.png ")) { log_assert(false && "can't load texture from file\n"); }
    if (!tex_off.loadFromFile("../../widget/img/button_off.png")) { log_assert(false && "can't load texture from file\n"); }

    are_texs_init = true;
}

//--------------------------------------------------------------------------------------------------

hold_button_t::hold_button_t(const vec2d    &pos_,
                             const vec2d    &size_,
                             const action_t &action_):
button_t(pos_, size_),
action  (action_)
{
    log_verify(dblcmp(pos_.x , 0) >= 0, ;);
    log_verify(dblcmp(pos_.y , 0) >= 0, ;);
    log_verify(dblcmp(size_.x, 0) >= 0, ;);
    log_verify(dblcmp(size_.y, 0) >= 0, ;);

    if (!are_texs_init) texs_init();
}
