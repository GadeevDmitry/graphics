#include <stdio.h>
#include "button/tool_button.h"

//==================================================================================================

const char *tool_button_t::BUTTON_TEXTURES_FILES[] =
{
    "../../widget/textures/button/fill_on.png",
    "../../widget/textures/button/rectangle_on.png",
    "../../widget/textures/button/ellipse_on.png",
    "../../widget/textures/button/polyline_on.png",
    "../../widget/textures/button/pencil_on.png",
    "../../widget/textures/button/line_on.png",
    "../../widget/textures/button/rubber_on.png",
    "../../widget/textures/button/spline_on.png",

    "../../widget/textures/button/fill_off.png",
    "../../widget/textures/button/rectangle_off.png",
    "../../widget/textures/button/ellipse_off.png",
    "../../widget/textures/button/polyline_off.png",
    "../../widget/textures/button/pencil_off.png",
    "../../widget/textures/button/line_off.png",
    "../../widget/textures/button/rubber_off.png",
    "../../widget/textures/button/spline_off.png"
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
