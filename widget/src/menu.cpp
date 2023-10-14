#include <stdio.h>
#include "menu.h"
#include "log.h"

//==================================================================================================

bool menu_t::on_key_press(const KEY_TYPE &key)
{
    if (on_key_press_func == nullptr)
        return on_widgets_key_press(key);

    return on_key_press_func(this, args, key, active);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_key_release(const KEY_TYPE &key)
{
    if (on_key_release_func == nullptr)
        return on_widgets_key_release(key);

    return on_key_release_func(this, args, key, active);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    const mouse_context_t &context = get_mouse_context();

    LOG_TAB_SERVICE_MESSAGE("MENU_T::ON_MOUSE_PRESS", "\n");
    LOG_TAB++;
    LOG_TAB_MESSAGE("activate = %p\n", active);

    if (active != this)
    {
        if (!region.is_point_inside(context.pos))
        {
            LOG_TAB_MESSAGE("POINT IS NOT INSIDE", "\n");
            LOG_TAB--;
            return false;
        }
        if (on_widgets_mouse_press (btn))
        {
            LOG_TAB_MESSAGE("SUB-WIDGETS SUCCESS", "\n");
            LOG_TAB--;
            return true;
        }
    }

    if (on_mouse_press_func != nullptr)
        on_mouse_press_func(this, args, btn, active);

    LOG_TAB--;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    if (active == this)
    {
        if (on_mouse_release_func == nullptr) return false;

        on_mouse_release_func(this, args, btn, active);
        return true;
    }

    return on_widgets_mouse_release(btn);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_move(const vec2d &off)
{
    if (active == this)
    {
        if (on_mouse_move_func == nullptr) return false;

        on_mouse_move_func(this, args, off, active);
        return true;
    }

    return on_widgets_mouse_move(off);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::activate_by_key_click(menu_t *self, void *args, const KEY_TYPE &key, widget_t *&active)
{
    LOG_VERIFY(active == nullptr, false);
    (void) args;
    (void) key;

    active = (widget_t *) self;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool menu_t::deactivate_by_key_click(menu_t *self, void *args, const KEY_TYPE &key, widget_t *&active)
{
    LOG_VERIFY(active == (widget_t *) self, false);
    (void) self;
    (void) args;
    (void) key;

    active = nullptr;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool menu_t::activate_by_mouse_click(menu_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active)
{
    LOG_VERIFY(active == nullptr, false);
    (void) args;
    (void) btn;

    active = (widget_t *) self;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool menu_t::deactivate_by_mouse_click(menu_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active)
{
    LOG_VERIFY(active == (widget_t *) self, false);
    (void) self;
    (void) args;
    (void) btn;

    active = nullptr;
    return true;
}
