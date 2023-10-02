#include <stdio.h>
#include "widget.h"

//==================================================================================================

KEY_TYPE widget_t::convert_key(const sf::Keyboard::Key sfml_key)
{
    if ((int) sfml_key < 0 || (int) sfml_key >= KEY_TYPE_COUNT)
        return KEY_TYPE_UNKNOWN;

    return (KEY_TYPE) sfml_key;
}

//--------------------------------------------------------------------------------------------------

MOUSE_BUTTON_TYPE widget_t::convert_mouse_btn(const sf::Mouse::Button sfml_mouse_btn)
{
    if ((int) sfml_mouse_btn < 0 || (int) sfml_mouse_btn >= MOUSE_BUTTON_TYPE_COUNT)
        return MOUSE_BUTTON_TYPE_UNKNOWN;

    return (MOUSE_BUTTON_TYPE) sfml_mouse_btn;
}
