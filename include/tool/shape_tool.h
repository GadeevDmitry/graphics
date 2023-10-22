#ifndef SHAPE_TOOL_H
#define SHAPE_TOOL_H

#include "tool.h"

//==================================================================================================

class shape_tool_t: public tool_t
{
// member functions
public:
    inline shape_tool_t();

// virtual
public:
    virtual void paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const color_t &color, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual void paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const color_t &color, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual void paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const color_t &color, const eventable::mouse_context_t &local_context, const vec2d             &off) override;

protected:
    virtual void draw_temp(render_texture_t &temp, const color_t &color) = 0;
};

//--------------------------------------------------------------------------------------------------

inline shape_tool_t::shape_tool_t():
tool_t()
{}

#endif // SHAPE_TOOL_H
