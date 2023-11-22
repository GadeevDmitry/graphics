#include <stdio.h>
#include "button/external_tool_button.h"

//==================================================================================================

bool external_tool_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    external_tool_button_t *tool_button = (external_tool_button_t *) handle;
    if (tool_button->tool != nullptr)
        tool_manager.set_tool(tool_button->tool);

    tool_button->status = widget_t::WIDGET_ACTIVATED;
    tool_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}
