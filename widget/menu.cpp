#include <stdio.h>
#include "menu.h"
#include "data_structs/include/log.h"

//==================================================================================================

bool menu_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == nullptr, false);

    if (controller.on_key_press(this, context, key)) return true;
    return on_subwidgets_key_press(context, key);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == nullptr, false);

    if (!visible.enclosing.is_point_inside(context.pos))
        return false;

    if (on_subwidgets_mouse_press(context, btn))
        return true;

    return controller.on_mouse_press(this, context, btn);
}