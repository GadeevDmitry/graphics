#include <stdio.h>
#include "button.h"
#include "data_structs/include/log.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

bool button_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    if (active == this)
        return controller.on_key_press(this, context, key);

    LOG_VERIFY(active == nullptr, false);
    return controller.on_key_press(this, context, key);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    if (active == this)
        return controller.on_mouse_press(this, context, btn);

    LOG_VERIFY(active == nullptr, false);

    if (!sub_enclosing.is_point_inside(context.pos))
        return false;

    return controller.on_mouse_press(this, context, btn);
}
