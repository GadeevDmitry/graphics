#include <stdio.h>
#include "menu.h"
#include "log.h"

//==================================================================================================

bool menu_t::on_key_press(const KEY_TYPE &key)
{
    LOG_ASSERT(active == nullptr || active == (widget_t *) this);

    if (active == nullptr && on_subwidgets_key_press(key))
        return true;

    if (on_key_press_func == nullptr) return false;
    return on_key_press_func(this, args, key);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_key_release(const KEY_TYPE &key)
{
    LOG_ASSERT(active == (widget_t *) this);
    if (on_key_release_func == nullptr) return false;

    return on_key_release_func(this, args, key);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_ASSERT(active == nullptr || active == (widget_t *) this);

    const mouse_context_t &context = get_mouse_context();
    if (!visible.region.is_point_inside(context.pos))
        return false;

    if (active == nullptr && on_subwidgets_mouse_press(btn))
        return false;

    if (on_mouse_press_func == nullptr) return false;
    return on_mouse_press_func(this, args, btn);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_ASSERT(active == (widget_t *) this);
    if (on_mouse_release_func == nullptr) return false;

    return on_mouse_release_func(this, args, btn);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_move(const vec2d &off)
{
    LOG_ASSERT(active == (widget_t *) this);
    if (on_mouse_move_func == nullptr) return false;

    return on_mouse_move_func(this, args, off);
}
