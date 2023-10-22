#include <stdio.h>
#include "desktop.h"

//==================================================================================================

bool desktop_t::refresh_after_event()
{
    if (update_struct())
    {
        recalc_areas();
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    bool res = false;
    if (active != nullptr) res = active->on_key_press   (context, key);
    else                   res = on_subwidgets_key_press(context, key);

    if (res) return refresh_after_event();
    return false;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    if (active == nullptr) return false;
    if (active->on_key_release(context, key)) return refresh_after_event();

    return false;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    bool res = false;
    if (active != nullptr) res = active->on_mouse_press   (context, btn);
    else                   res = on_subwidgets_mouse_press(context, btn);

    if (res) return refresh_after_event();
    return false;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    if (active == nullptr) return false;
    if (active->on_mouse_release(context, btn)) return refresh_after_event();

    return false;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    if (active == nullptr) return false;
    if (active->on_mouse_move(context, off)) return refresh_after_event();

    return false;
}
