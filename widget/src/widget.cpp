#include <stdio.h>
#include "widget.h"

//==================================================================================================

widget_t::mouse_context_t widget_t::saved_mouse_context(vec2d(0, 0), MOUSE_BUTTON_TYPE_UNKNOWN);
KEY_TYPE                  widget_t::saved_key = KEY_TYPE_UNKNOWN;

//==================================================================================================

widget_t::mouse_context_t::mouse_context_t():
pos(),
btn(MOUSE_BUTTON_TYPE_UNKNOWN)
{}

//--------------------------------------------------------------------------------------------------

widget_t::mouse_context_t::mouse_context_t(const vec2d &pos_, const MOUSE_BUTTON_TYPE &btn_):
pos(pos_),
btn(btn_)
{}

//--------------------------------------------------------------------------------------------------

const KEY_TYPE &widget_t::refresh_key(const sf::Keyboard::Key &sfml_key)
{
    KEY_TYPE cur_key = KEY_TYPE_UNKNOWN;

    if ((int) sfml_key > (int) KEY_TYPE_UNKNOWN &&
        (int) sfml_key < (int) KEY_TYPE_COUNT)
        cur_key = (KEY_TYPE) sfml_key;

    return saved_key = cur_key;
}

//--------------------------------------------------------------------------------------------------

const widget_t::mouse_context_t &widget_t::refresh_mouse_context(const sf::Mouse::Button &sfml_mouse_btn,
                                                                 const sf::Vector2i      &sfml_mouse_pos)
{
    MOUSE_BUTTON_TYPE cur_btn = MOUSE_BUTTON_TYPE_UNKNOWN;

    if ((int) sfml_mouse_btn > (int) MOUSE_BUTTON_TYPE_UNKNOWN &&
        (int) sfml_mouse_btn < (int) MOUSE_BUTTON_TYPE_COUNT)
        cur_btn = (MOUSE_BUTTON_TYPE) sfml_mouse_btn;

    saved_mouse_context.btn = cur_btn;
    saved_mouse_context.pos = vec2d((double) sfml_mouse_pos.x, (double) sfml_mouse_pos.y);

    return saved_mouse_context;
}

//--------------------------------------------------------------------------------------------------

const widget_t::mouse_context_t &widget_t::refresh_mouse_pos(const sf::Vector2i &sfml_mouse_pos)
{
    saved_mouse_context.pos = vec2d((double) sfml_mouse_pos.x, (double) sfml_mouse_pos.y);
    return saved_mouse_context;
}
