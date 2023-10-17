#ifndef SHAPE_TOOL_H
#define SHAPE_TOOL_H

#include "tool.h"

//==================================================================================================

class shape_tool_t: public tool_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    void virtual draw_temp(render_texture_t &temp, const color_t &color) = 0;

public:
    inline shape_tool_t();

    void virtual paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const color_t &color, const vec2d &texture_off, const MOUSE_BUTTON_TYPE &btn) override;
    void virtual paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const color_t &color, const vec2d &texture_off, const MOUSE_BUTTON_TYPE &btn) override;
    void virtual paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const color_t &color, const vec2d &texture_off, const vec2d             &off) override;
};

//--------------------------------------------------------------------------------------------------

inline shape_tool_t::shape_tool_t():
tool_t()
{}

#endif // SHAPE_TOOL_H
