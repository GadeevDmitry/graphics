#include <stdio.h>
#include "desktop.h"

//==================================================================================================

bool desktop_t::refresh_after_event()
{
    if (update_struct())
    {
        recalc_regions();
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

    return res;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    if (active == nullptr) return false;
    return active->on_key_release(context, key);
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    bool res = false;
    if (active != nullptr) res = active->on_mouse_press   (context, btn);
    else                   res = on_subwidgets_mouse_press(context, btn);

    return res;
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    if (active == nullptr) return false;
    return active->on_mouse_release(context, btn);
}

//--------------------------------------------------------------------------------------------------

bool desktop_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    if (active == nullptr) return false;
    return active->on_mouse_move(context, off);
}

//--------------------------------------------------------------------------------------------------

void desktop_t::render_initial(render_texture_t &wnd)
{
    recalc_regions();
    wnd.draw_rectangle(background, own_visible);
    subwidgets_render(wnd);
}

//--------------------------------------------------------------------------------------------------

void desktop_t::render(render_texture_t &wnd)
{
    if (refresh_after_event())
    {
        wnd.draw_rectangle(background, own_visible);
        subwidgets_render(wnd);
    }
}
