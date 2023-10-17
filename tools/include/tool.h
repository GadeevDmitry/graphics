#ifndef TOOL_H
#define TOOL_H

#include "canvas.h"
#include "render_texture.h"

//==================================================================================================

class tool_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    vec2d start;
    vec2d last;

public:
    explicit inline  tool_t();
    virtual  inline ~tool_t() {}

    virtual void deactivate            () {}
    virtual void paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const color_t &color, const vec2d &texture_off, const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual void paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const color_t &color, const vec2d &texture_off, const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual void paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const color_t &color, const vec2d &textute_off, const vec2d             &off) = 0;
};

//--------------------------------------------------------------------------------------------------

tool_t::tool_t():
start    (),
last     ()
{}

#endif // TOOL_H
