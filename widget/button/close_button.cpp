#include <stdio.h>
#include "button/close_button.h"

//==================================================================================================

const char *close_button_t::BUTTON_TEXTURES_FILES[] =
{
    "../../widget/textures/button/red_close.png",
    "../../widget/textures/button/blue_close.png",
    "../../widget/textures/button/green_close.png",
};

texture_t close_button_t::BUTTON_TEXTURES[sizeof(BUTTON_TEXTURES_FILES) / sizeof(char *)] = {};

//==================================================================================================

bool close_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;

    close_button_t *close_btn = (close_button_t *) handle;

    close_btn->to_close.status = widget_t::WIDGET_CLOSED;
    close_btn->to_close.update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void close_button_t::load_textures()
{
    for (size_t i = 0; i * sizeof(char *) < sizeof(BUTTON_TEXTURES_FILES); ++i)
    {
        BUTTON_TEXTURES[i].load_from_file(BUTTON_TEXTURES_FILES[i]);
    }
};
