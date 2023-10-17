#include <stdio.h>
#include "button.h"
#include "log.h"
#include "algorithm.h"

//==================================================================================================

const char *button_t::BUTTON_TEXTURES_FILENAMES[] =
{
    // relative to examples/exapmle_name
    "../../widget/textures/button/red_winapi.png",
    "../../widget/textures/button/blue_winapi.png",
    "../../widget/textures/button/green_winapi.png",

    "../../widget/textures/button/line_on.png",
    "../../widget/textures/button/line_off.png",
    "../../widget/textures/button/pencil_on.png",
    "../../widget/textures/button/pencil_off.png",
    "../../widget/textures/button/rubber_on.png",
    "../../widget/textures/button/rubber_off.png",
    "../../widget/textures/button/ellipse_on.png",
    "../../widget/textures/button/ellipse_off.png",
    "../../widget/textures/button/rectangle_on.png",
    "../../widget/textures/button/rectangle_off.png",

    "../../widget/textures/button/white_on.png",
    "../../widget/textures/button/white_off.png",
    "../../widget/textures/button/blue_on.png",
    "../../widget/textures/button/blue_off.png",
    "../../widget/textures/button/red_on.png",
    "../../widget/textures/button/red_off.png",
    "../../widget/textures/button/orange_on.png",
    "../../widget/textures/button/orange_off.png",
    "../../widget/textures/button/green_on.png",
    "../../widget/textures/button/green_off.png",
    "../../widget/textures/button/black_on.png",
    "../../widget/textures/button/black_off.png",
};

//--------------------------------------------------------------------------------------------------

texture_t button_t::BUTTON_TEXTURES[sizeof(BUTTON_TEXTURES_FILENAMES) / sizeof(char *)] = {};

//==================================================================================================

void button_t::load_textures()
{
    for (size_t i = 0; i * sizeof(char *) < sizeof(BUTTON_TEXTURES_FILENAMES); ++i)
    {
        BUTTON_TEXTURES[i].load_from_file(BUTTON_TEXTURES_FILENAMES[i]);
    }
};

//--------------------------------------------------------------------------------------------------

bool button_t::on_key_press(const KEY_TYPE &key)
{
    LOG_ASSERT(active == nullptr || active == (widget_t *) this);
    if (on_key_press_func == nullptr) return false;

    return on_key_press_func(this, args, key);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_key_release(const KEY_TYPE &key)
{
    LOG_ASSERT(active == (widget_t *) this);
    if (on_key_release_func == nullptr) return false;

    return on_key_release_func(this, args, key);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_ASSERT(active == nullptr || active == (widget_t *) this);
    if (on_mouse_press_func == nullptr) return false;

    const mouse_context_t &context = get_mouse_context();
    if (!visible.region.is_point_inside(context.pos)) return false;

    return on_mouse_press_func(this, args, btn);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_ASSERT(active == (widget_t *) this);
    if (on_mouse_release_func == nullptr) return false;

    return on_mouse_release_func(this, args, btn);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_move(const vec2d &off)
{
    LOG_ASSERT(active == (widget_t *) this);
    if (on_mouse_move_func == nullptr) return false;

    return on_mouse_move_func(this, args, off);
}
