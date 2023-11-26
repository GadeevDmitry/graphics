#include <stdio.h>
#include "eventable.h"

//==================================================================================================

KEY_TYPE eventable::key_context_t::convert_sfml_key(const sf::Keyboard::Key &sfml_key)
{
    if ((int) sfml_key <= KEY_TYPE_UNKNOWN ||
        (int) sfml_key >= KEY_TYPE_COUNT)
    {
        return KEY_TYPE_UNKNOWN;
    }

    return (KEY_TYPE) sfml_key;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MOUSE_BUTTON_TYPE eventable::mouse_context_t::convert_sfml_btn(const sf::Mouse::Button &sfml_mouse_btn)
{
    if ((int) sfml_mouse_btn <= KEY_TYPE_UNKNOWN ||
        (int) sfml_mouse_btn >= KEY_TYPE_COUNT)
    {
        return MOUSE_BUTTON_TYPE_UNKNOWN;
    }

    return (MOUSE_BUTTON_TYPE) sfml_mouse_btn;
}

//--------------------------------------------------------------------------------------------------

vec2d eventable::mouse_context_t::convert_sfml_pos(const sf::Vector2i &sfml_mouse_pos)
{
    return vec2d((double) sfml_mouse_pos.x, (double) sfml_mouse_pos.y);
}
