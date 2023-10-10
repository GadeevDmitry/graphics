#include <stdio.h>
#include "button.h"
#include "log.h"

//==================================================================================================

bool button_t::on_key_press(const KEY_TYPE &key)
{
    LOG_VERIFY(saved_key == KEY_TYPE_UNKNOWN, false);

    if (on_key_press_func == nullptr) return false;

    bool res = on_key_press_func(args, key);
    if (res) saved_key = key;

    return res;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_key_release(const KEY_TYPE &key)
{
    if (saved_key == KEY_TYPE_UNKNOWN) return false;

    LOG_VERIFY(saved_key == key, false);

    saved_key = KEY_TYPE_UNKNOWN;
    if (on_key_release_func != nullptr)
        on_key_release_func(args, key);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_press(const mouse_context_t &context)
{
    LOG_VERIFY(saved_mouse_btn == MOUSE_BUTTON_TYPE_UNKNOWN, false);

    if (!region.is_point_inside(context.pos)) return false;

    saved_mouse_btn = context.btn;
    if (on_mouse_press_func != nullptr)
        on_mouse_press_func(args, context);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_release(const mouse_context_t &context)
{
    if (saved_mouse_btn == MOUSE_BUTTON_TYPE_UNKNOWN) return false;

    LOG_VERIFY(saved_mouse_btn == context.btn, false);

    saved_mouse_btn = MOUSE_BUTTON_TYPE_UNKNOWN;
    if (on_mouse_release_func != nullptr)
        on_mouse_release_func(args, context);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_move(const mouse_context_t &context)
{
    if (saved_mouse_btn == MOUSE_BUTTON_TYPE_UNKNOWN) return false;

    LOG_VERIFY(saved_mouse_btn == context.btn, false);

    if (on_mouse_move_func != nullptr)
        on_mouse_move_func(args, context);

    return true;
}
