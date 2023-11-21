#include <stdio.h>
#include "button/palette_button.h"

//==================================================================================================

const char *palette_button_t::BUTTON_TEXTURES_FILES[] =
{
    "assets/textures/button/white_on.png",
    "assets/textures/button/blue_on.png",
    "assets/textures/button/red_on.png",
    "assets/textures/button/orange_on.png",
    "assets/textures/button/green_on.png",
    "assets/textures/button/black_on.png",

    "assets/textures/button/white_off.png",
    "assets/textures/button/blue_off.png",
    "assets/textures/button/red_off.png",
    "assets/textures/button/orange_off.png",
    "assets/textures/button/green_off.png",
    "assets/textures/button/black_off.png",
};

texture_t palette_button_t::BUTTON_TEXTURES[sizeof(BUTTON_TEXTURES_FILES) / sizeof(char *)] = {};

//==================================================================================================

bool palette_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    palette_button_t *palette_button = (palette_button_t *) handle;
    tool_manager.set_color(palette_button->color);

    palette_button->status = widget_t::WIDGET_ACTIVATED;
    palette_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void palette_button_t::load_textures()
{
    for (size_t i = 0; i * sizeof(char *) < sizeof(BUTTON_TEXTURES_FILES); ++i)
    {
        BUTTON_TEXTURES[i].load_from_file(BUTTON_TEXTURES_FILES[i]);
    }
};
