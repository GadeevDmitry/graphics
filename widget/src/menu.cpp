#include <stdio.h>
#include "menu.h"
#include "log.h"

//==================================================================================================

bool menu_t::on_mouse_press(const mouse_context_t &context)
{
    LOG_VERIFY(saved_mouse_btn == MOUSE_BUTTON_TYPE_UNKNOWN, false);
    mouse_context_t context_rel = context - region.ld_corner;

    if (!region.is_point_inside(context.pos)) return false;
    if (on_widgets_mouse_press (context_rel)) return true;

    saved_mouse_btn = context.btn;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_release(const mouse_context_t &context)
{
    mouse_context_t context_rel = context - region.ld_corner;

    if (saved_mouse_btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        return on_widgets_mouse_release(context_rel);

    LOG_VERIFY(saved_mouse_btn == context.btn, false);

    saved_mouse_btn = MOUSE_BUTTON_TYPE_UNKNOWN;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_move(const mouse_context_t &context)
{
    if (saved_mouse_btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        return on_widgets_mouse_move(context);

    LOG_VERIFY(saved_mouse_btn == context.btn, false);

    if (on_mouse_move_func != nullptr)
        on_mouse_move_func(args, context);

    return true;
}
