#ifndef TOOL_H
#define TOOL_H

#include "widget.h"
#include "render_texture.h"

//==================================================================================================

class tool
{
public:
    inline   tool() {}
    virtual ~tool() {}

    virtual void deactive() = 0;
    virtual void paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual void paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual void paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const vec2d             &off) = 0;
};

#endif // TOOL_H
