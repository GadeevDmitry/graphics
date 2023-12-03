#include <stdio.h>
#include "window/modal_window.h"
#include "event/event_manager.h"

//==================================================================================================

modal_window_t::modal_window_t(event_manager_t &event_manager_, const color_t &color_, const char *wnd_name):
window_t     (color_, wnd_name),
event_manager(event_manager_)
{
    event_manager.set_all_priorities(1);
    event_manager.register_child(eventable_proxy(this));
    event_priority = 1;
}

//--------------------------------------------------------------------------------------------------

modal_window_t::modal_window_t(event_manager_t &event_manager_, const rectangle_t &enclosing_, const color_t &color_, const char *wnd_name):
window_t     (enclosing_, color_, wnd_name),
event_manager(event_manager_)
{
    event_manager.set_all_priorities(1);
    event_manager.register_child(eventable_proxy(this));
    event_priority = 1;
}

//--------------------------------------------------------------------------------------------------

modal_window_t::~modal_window_t()
{
    event_manager.set_all_priorities(0);
    event_manager.unregister_child(eventable_proxy(this));
}

//--------------------------------------------------------------------------------------------------

bool modal_window_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    if (active != nullptr) return active->on_key_press(context, key);
    return window_t::on_key_press(context, key);
}

//--------------------------------------------------------------------------------------------------

inline bool modal_window_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    if (active != nullptr) return active->on_key_release(context, key);
    return false;
}

//--------------------------------------------------------------------------------------------------

bool modal_window_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    if (active != nullptr) return active->on_mouse_press(context, btn);
    return window_t::on_mouse_press(context, btn);
}

//--------------------------------------------------------------------------------------------------

inline bool modal_window_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    if (active != nullptr) return active->on_mouse_release(context, btn);
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool modal_window_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    if (active != nullptr) return active->on_mouse_move(context, off);
    return false;
}
