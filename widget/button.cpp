#include <stdio.h>
#include "button.h"
#include "data_structs/include/log.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

bool button_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == nullptr, false);

    if (!visible.enclosing.is_point_inside(context.pos))
        return false;

    return controller.on_mouse_press(this, context, btn);
}
