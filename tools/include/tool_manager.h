#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "log.h"
#include "tool.h"
#include "color.h"
#include "widget.h"
#include "render_texture.h"

//==================================================================================================

class tool_manager_t
{
private:
    tool    *active_tool;
    color_t color;

public:
    inline          tool_manager_t();
    inline explicit tool_manager_t(const color_t &color_);
    inline         ~tool_manager_t();

    inline void set_color(const color_t &color_);
    inline void set_tool (tool    *active_tool_);

    inline void paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const MOUSE_BUTTON_TYPE &btn);
    inline void paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const MOUSE_BUTTON_TYPE &btn);
    inline void paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const vec2d             &off);
};

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t():
active_tool(nullptr),
color      ()
{}

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t(const color_t &color_):
active_tool(nullptr),
color      (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_color(const color_t &color_)
{
    color = color_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_tool(tool *active_tool_)
{
    if (active_tool == nullptr)
    {
        active_tool = active_tool_;
        return;
    }

    active_tool->deactive();
    active_tool = active_tool_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_press(render_texture_t &perm, render_texture_t &temp, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active_tool != nullptr, (void) 0);
    active_tool->paint_on_mouse_press(perm, temp, btn);
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active_tool != nullptr, (void) 0);
    active_tool->paint_on_mouse_release(perm, temp, btn);
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_move(render_texture_t &perm, render_texture_t &temp, const vec2d &off)
{
    LOG_VERIFY(active_tool != nullptr, (void) 0);
    active_tool->paint_on_mouse_move(perm, temp, off);
}

#endif // TOOL_MANAGER_H
