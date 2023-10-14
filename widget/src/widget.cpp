#include <stdio.h>
#include "widget.h"
#include "log.h"

//==================================================================================================

key_context_t   widget_t::saved_key_context;
mouse_context_t widget_t::saved_mouse_context;
widget_t       *widget_t::active = nullptr;

//==================================================================================================

KEY_TYPE key_context_t::convert_sfml(const sf::Keyboard::Key &sfml_key)
{
    if ((int) sfml_key <= KEY_TYPE_UNKNOWN ||
        (int) sfml_key >= KEY_TYPE_COUNT)
    {
        return KEY_TYPE_UNKNOWN;
    }

    return (KEY_TYPE) sfml_key;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MOUSE_BUTTON_TYPE mouse_context_t::convert_sfml(const sf::Mouse::Button &sfml_mouse_btn)
{
    if ((int) sfml_mouse_btn <= KEY_TYPE_UNKNOWN ||
        (int) sfml_mouse_btn >= KEY_TYPE_COUNT)
    {
        return MOUSE_BUTTON_TYPE_UNKNOWN;
    }

    return (MOUSE_BUTTON_TYPE) sfml_mouse_btn;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"

bool widget_t::refresh_context_on_key_press(const KEY_TYPE &pressed_key)
{
    if (pressed_key == KEY_TYPE_UNKNOWN)
        return false;

    if (pressed_key >= LControl && pressed_key <= RSystem)
    {
        switch (pressed_key)
        {
            case LControl:
            case RControl: saved_key_context.control = true; break;

            case LAlt    :
            case RAlt    : saved_key_context.alt     = true; break;

            case LShift  :
            case RShift  : saved_key_context.shift   = true; break;

            case LSystem :
            case RSystem : saved_key_context.system  = true; break;

            default: break;
        }

        return false;
    }

    if (saved_key_context.key != KEY_TYPE_UNKNOWN)
        return false;

    saved_key_context.key = pressed_key;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool widget_t::refresh_context_on_key_release(const KEY_TYPE &released_key)
{

    if (released_key == KEY_TYPE_UNKNOWN)
        return false;

    if (released_key >= LControl && released_key <= RSystem)
    {
        switch (released_key)
        {
            case LControl:
            case RControl: saved_key_context.control = false; break;

            case LAlt    :
            case RAlt    : saved_key_context.alt     = false; break;

            case LShift  :
            case RShift  : saved_key_context.shift   = false; break;

            case LSystem :
            case RSystem : saved_key_context.system  = false; break;

            default: break;
        }
    }

    if (saved_key_context.key != released_key)
        return false;

    saved_key_context.key = KEY_TYPE_UNKNOWN;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool widget_t::refresh_context_on_mouse_press(const MOUSE_BUTTON_TYPE &pressed_btn)
{
    if (pressed_btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        return false;

    switch (pressed_btn)
    {
        case Left  : saved_mouse_context.left   = true; break;
        case Right : saved_mouse_context.right  = true; break;
        case Middle: saved_mouse_context.middle = true; break;

        default: break;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------

bool widget_t::refresh_context_on_mouse_release(const MOUSE_BUTTON_TYPE &released_btn)
{
    if (released_btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        return false;

    switch (released_btn)
    {
        case Left  : saved_mouse_context.left   = false; break;
        case Right : saved_mouse_context.right  = false; break;
        case Middle: saved_mouse_context.middle = false; break;

        default: break;
    }

    return true;
}

#pragma GCC diagnostic pop

//--------------------------------------------------------------------------------------------------

vec2d widget_t::refresh_context_on_mouse_move(const sf::Vector2i &pos_)
{
    vec2d pos((double) pos_.x, (double) pos_.y);
    vec2d offset = pos - saved_mouse_context.pos;

    saved_mouse_context.pos = pos;
    return offset;
}

//--------------------------------------------------------------------------------------------------

void widget_t::process_key_press_event(widget_t &system, const KEY_TYPE &pressed_key)
{
    if (!refresh_context_on_key_press(pressed_key))
        return;

    bool res = false;

    if (active != nullptr) res = active->on_key_press(pressed_key);
    else                   res = system .on_key_press(pressed_key);

    if (res) system.recalc_region();
}

//--------------------------------------------------------------------------------------------------

void widget_t::process_key_release_event(widget_t &system, const KEY_TYPE &released_key)
{
    if (!refresh_context_on_key_release(released_key))
        return;

    bool res = false;

    if (active != nullptr) res = active->on_key_release(released_key);
    else                   res = system .on_key_release(released_key);

    if (res) system.recalc_region();
}

//--------------------------------------------------------------------------------------------------

void widget_t::process_mouse_press_event(widget_t &system, const MOUSE_BUTTON_TYPE &pressed_btn)
{
    if (!refresh_context_on_mouse_press(pressed_btn))
        return;

    LOG_TAB_SERVICE_MESSAGE("PROCESS MOUSE_PRESS", "\n");
    LOG_TAB++;
    LOG_TAB_MESSAGE("active = %p\n", active);

    bool res = false;

    if (active != nullptr) res = active->on_mouse_press(pressed_btn);
    else                   res = system .on_mouse_press(pressed_btn);

    if (res) system.recalc_region();

    LOG_TAB--;
}

//--------------------------------------------------------------------------------------------------

void widget_t::process_mouse_release_event(widget_t &system, const MOUSE_BUTTON_TYPE &released_btn)
{
    if (!refresh_context_on_mouse_release(released_btn))
        return;

    LOG_TAB_SERVICE_MESSAGE("PROCESS MOUSE_RELEASE", "\n");
    LOG_TAB++;
    LOG_TAB_MESSAGE("active = %p\n", active);

    bool res = false;

    if (active != nullptr) res = active->on_mouse_release(released_btn);
    else                   res = system .on_mouse_release(released_btn);

    if (res) system.recalc_region();

    LOG_TAB--;
}

//--------------------------------------------------------------------------------------------------

void widget_t::process_mouse_move_event(widget_t &system, const sf::Vector2i &pos)
{
    vec2d off = refresh_context_on_mouse_move(pos);
    if (active == nullptr) return;

    LOG_TAB_SERVICE_MESSAGE("PROCESS MOUSE_MOVE", "\n");
    LOG_TAB++;
    LOG_TAB_MESSAGE("active = %p\n", active);

    bool res = active->on_mouse_move(off);
    if (res) system.recalc_region();

    LOG_TAB--;
}
