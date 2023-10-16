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
    "../../widget/textures/button/green_winapi.png"
};

//--------------------------------------------------------------------------------------------------

texture_t button_t::BUTTON_TEXTURES[3] = {};

//==================================================================================================

void button_t::load_textures()
{
    for (size_t i = 0; i * sizeof(char *) < sizeof(BUTTON_TEXTURES_FILENAMES); ++i)
    {
        bool res = BUTTON_TEXTURES[i].load_from_file(BUTTON_TEXTURES_FILENAMES[i]);
        LOG_TAB_MESSAGE("LOADING TEXTURE #%lu (%s) returned %d\n", i, BUTTON_TEXTURES_FILENAMES[i], res);
    }
};

//--------------------------------------------------------------------------------------------------

bool button_t::on_key_press(const KEY_TYPE &key)
{
    if (on_key_press_func == nullptr) return false;
    return on_key_press_func(this, args, key, active);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_key_release(const KEY_TYPE &key)
{
    if (on_key_release_func == nullptr) return false;
    return on_key_release_func(this, args, key, active);
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    const mouse_context_t &context = get_mouse_context();

    if (!region.is_point_inside(context.pos)) return false;
    if (on_mouse_press_func != nullptr)
        on_mouse_press_func(this, args, btn, active);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    if (on_mouse_release_func == nullptr) return false;

    on_mouse_release_func(this, args, btn, active);
    return true;
}

//--------------------------------------------------------------------------------------------------

bool button_t::on_mouse_move(const vec2d &off)
{
    LOG_VERIFY(active == this, false);

    if (on_mouse_move_func == nullptr) return false;

    on_mouse_move_func(this, args, off, active);
    return true;
}

//--------------------------------------------------------------------------------------------------

void button_t::activate_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active)
{
    LOG_VERIFY(active == nullptr, (void) 0);
    (void) args;
    (void) btn;

    active = (widget_t *) self;
}

//--------------------------------------------------------------------------------------------------

void button_t::deactivate_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &key, widget_t *&active)
{
    LOG_VERIFY(active == (widget_t *) self, (void) 0);
    (void) self;
    (void) args;
    (void) key;

    active = nullptr;
}

//--------------------------------------------------------------------------------------------------

void button_t::close_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active)
{
    LOG_VERIFY(args != nullptr, (void) 0);
    widget_t &arg = *(widget_t *) args;

    (void) self;
    (void) btn;
    (void) active;

    arg.status = WIDGET_CLOSED;
    active     = nullptr;
}
