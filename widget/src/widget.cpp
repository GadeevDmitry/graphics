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

void widget_t::refresh_key(const sf::Keyboard::Key &sfml_key)
{
    KEY_TYPE cur_key = KEY_TYPE_UNKNOWN;

    if ((int) sfml_key > (int) KEY_TYPE_UNKNOWN &&
        (int) sfml_key < (int) KEY_TYPE_COUNT)
        cur_key = (KEY_TYPE) sfml_key;
    else
        return;

    if (saved_key == cur_key)
        saved_key = KEY_TYPE_UNKNOWN;       // release
    else if (saved_key == KEY_TYPE_UNKNOWN)
        saved_key = cur_key;                // press
}

//--------------------------------------------------------------------------------------------------

void widget_t::refresh_mouse_btn(const sf::Mouse::Button &sfml_mouse_bnt)
{
    MOUSE_BUTTON_TYPE cur_btn = MOUSE_BUTTON_TYPE_UNKNOWN;

    if ((int) sfml_mouse_bnt > (int) MOUSE_BUTTON_TYPE_UNKNOWN &&
        (int) sfml_mouse_bnt < (int) MOUSE_BUTTON_TYPE_COUNT)
        cur_btn = (MOUSE_BUTTON_TYPE) sfml_mouse_bnt;
    else
        return;

    if (saved_mouse_context.btn == cur_btn)
        saved_mouse_context.btn = MOUSE_BUTTON_TYPE_UNKNOWN;        // release
    else if (saved_mouse_context.btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        saved_mouse_context.btn = cur_btn;                          // press
}

//--------------------------------------------------------------------------------------------------

void widget_t::refresh_mouse_pos(const sf::Vector2i &sfml_mouse_pos)
{
    vec2d cur_pos((double) sfml_mouse_pos.x, (double) sfml_mouse_pos.y);
    saved_mouse_context.pos = cur_pos - saved_mouse_context.pos;
}
