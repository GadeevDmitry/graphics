#include <stdio.h>
#include "button/tool_button.h"

//==================================================================================================

const char *tool_button_t::BUTTON_TEXTURES_FILES[] =
{
    "assets/textures/button/fill_on.png",
    "assets/textures/button/rectangle_on.png",
    "assets/textures/button/ellipse_on.png",
    "assets/textures/button/polyline_on.png",
    "assets/textures/button/pencil_on.png",
    "assets/textures/button/line_on.png",
    "assets/textures/button/rubber_on.png",
    "assets/textures/button/spline_on.png",

    "assets/textures/button/fill_off.png",
    "assets/textures/button/rectangle_off.png",
    "assets/textures/button/ellipse_off.png",
    "assets/textures/button/polyline_off.png",
    "assets/textures/button/pencil_off.png",
    "assets/textures/button/line_off.png",
    "assets/textures/button/rubber_off.png",
    "assets/textures/button/spline_off.png"
};

texture_t tool_button_t::BUTTON_TEXTURES[sizeof(BUTTON_TEXTURES_FILES) / sizeof(char *)] = {};

//==================================================================================================

bool tool_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    tool_button_t *tool_button = (tool_button_t *) handle;
    if (tool_button->tool != nullptr)
        tool_manager.set_tool(tool_button->tool);

    tool_button->status = widget_t::WIDGET_ACTIVATED;
    tool_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void tool_button_t::load_textures()
{
    for (size_t i = 0; i * sizeof(char *) < sizeof(BUTTON_TEXTURES_FILES); ++i)
    {
        BUTTON_TEXTURES[i].load_from_file(BUTTON_TEXTURES_FILES[i]);
    }
};
