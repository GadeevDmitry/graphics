#include <stdio.h>
#include "button.h"
#include "log.h"

//==================================================================================================

bool button_t::on_key_press(const KEY_TYPE &key)
{
    if (on_key_press_func == nullptr) return false;
    return on_key_press_func(this, args, key, active);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_key_release(const KEY_TYPE &key)
{
    if (on_key_release_func == nullptr) return false;
    return on_key_release_func(this, args, key, active);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    const mouse_context_t &context = get_mouse_context();

    if (!region.is_point_inside(context.pos)) return false;
    if (on_mouse_press_func != nullptr)
        on_mouse_press_func(this, args, btn, active);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    if (on_mouse_release_func == nullptr) return false;

    on_mouse_release_func(this, args, btn, active);
    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_move(const vec2d &off)
{
    LOG_VERIFY(active == this, false);

    if (on_mouse_move_func == nullptr) return false;

    on_mouse_move_func(this, args, off, active);
    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::activate_by_key_click(button_t *self, void *args, const KEY_TYPE &key, widget_t *&active)
{
    LOG_VERIFY(active == nullptr, false);
    (void) args;
    (void) key;

    active = (widget_t *) self;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::deactivate_by_key_click(button_t *self, void *args, const KEY_TYPE &key, widget_t *&active)
{
    LOG_VERIFY(active == (widget_t *) self, false);
    (void) self;
    (void) args;
    (void) key;

    active = nullptr;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::activate_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active)
{
    LOG_VERIFY(active == nullptr, false);
    (void) args;
    (void) btn;

    active = (widget_t *) self;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::deactivate_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &key, widget_t *&active)
{
    LOG_VERIFY(active == (widget_t *) self, false);
    (void) self;
    (void) args;
    (void) key;

    active = nullptr;
    return true;
}
