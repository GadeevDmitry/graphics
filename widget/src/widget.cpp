#include <stdio.h>
#include "widget.h"

//==================================================================================================

KEY_TYPE widget_t::key_t(const sf::Keyboard::Key &sfml_key)
{
    if ((int) sfml_key < 0 || (int) sfml_key >= KEY_TYPE_COUNT)
        return KEY_TYPE_UNKNOWN;

    return (KEY_TYPE) sfml_key;
}

//--------------------------------------------------------------------------------------------------

widget_t::mouse_context_t::mouse_context_t(const sf::Mouse::Button &sfml_mouse_btn_,
                                           const sf::Vector2i      &sfml_mouse_pos_):
pos((double) sfml_mouse_pos_.x, (double) sfml_mouse_pos_.y),
btn(MOUSE_BUTTON_TYPE_UNKNOWN)
{
    if (((int) sfml_mouse_btn_ < (int) MOUSE_BUTTON_TYPE_COUNT) &&
        ((int) sfml_mouse_btn_ > (int) MOUSE_BUTTON_TYPE_UNKNOWN))
    {
        btn = (MOUSE_BUTTON_TYPE) sfml_mouse_btn_;
    }
}

//--------------------------------------------------------------------------------------------------

void widget_t::updateRegions (clipping_region_t &region) {
    visible -= region;
}
