#include <stdio.h>
#include "eventable_proxy.h"

//==================================================================================================

bool eventable_proxy::on_key_press(const eventable::key_context_t &context, const KEY_TYPE &key) const
{
    if (is_internal) return internal->on_key_press(context, key);
    return external->on_key_press(plugin::KeyboardContext(context, key));
}

//--------------------------------------------------------------------------------------------------

bool eventable_proxy::on_key_release(const eventable::key_context_t &context, const KEY_TYPE &key) const
{
    if (is_internal) return internal->on_key_release(context, key);
    return external->on_key_release(plugin::KeyboardContext(context, key));
}

//--------------------------------------------------------------------------------------------------

bool eventable_proxy::on_mouse_press(const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) const
{
    if (is_internal) return internal->on_mouse_press(context, btn);

    if (btn == MOUSE_BUTTON_MIDDLE) return false;
    return external->on_mouse_press(plugin::MouseContext(context, btn));
}

//--------------------------------------------------------------------------------------------------

bool eventable_proxy::on_mouse_release(const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) const
{
    if (is_internal) return internal->on_mouse_release(context, btn);

    if (btn == MOUSE_BUTTON_MIDDLE) return false;
    return external->on_mouse_release(plugin::MouseContext(context, btn));
}

//--------------------------------------------------------------------------------------------------

bool eventable_proxy::on_mouse_move(const eventable::mouse_context_t &context, const vec2d &off) const
{
    if (is_internal) return internal->on_mouse_move(context, off);
    return external->on_mouse_move(plugin::MouseContext(context, off));
}
