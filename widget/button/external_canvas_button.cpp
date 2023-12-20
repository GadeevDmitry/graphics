#include <stdio.h>
#include "button/external_canvas_button.h"

//==================================================================================================

bool external_canvas_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    external_canvas_button_t *canvas_button = (external_canvas_button_t *) handle;
    if (canvas_button->canvas_window != nullptr)
    {
        canvas_button->canvas_window->status = widget_t::WIDGET_ACTIVATED;
        canvas_button->canvas_window->update_ancestral_status(widget_t::WIDGET_ACTIVATED);
    }

    canvas_button->status = widget_t::WIDGET_ACTIVATED;
    canvas_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}
