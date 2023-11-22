#include <stdio.h>
#include "button/external_palette_button.h"

//==================================================================================================

bool external_palette_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    external_palette_button_t *palette_button = (external_palette_button_t *) handle;
    tool_manager.set_color(palette_button->color);

    palette_button->status = widget_t::WIDGET_ACTIVATED;
    palette_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}
