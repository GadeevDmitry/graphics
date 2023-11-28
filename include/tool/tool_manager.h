#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "plugin/standart/Tool.h"
#include "widget/canvas.h"

//==================================================================================================

using plugin::ToolI;

namespace host
{
    class HostToolManagerI;
}

class tool_manager_t
{
// member functions
public:
             inline  tool_manager_t();
    explicit inline  tool_manager_t(ToolI *last_tool, const color_t &color);
             inline ~tool_manager_t() {}

    void inline set_color(const color_t &color);
    void inline set_tool (ToolI *tool);

    void paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn);
    void paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn);
    void paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const vec2d             &off);

// member data
private:
    ToolI *last_tool;
    color_t    color;

// friends
    friend host::HostToolManagerI;
};

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t():
last_tool(nullptr),
color    ()
{}

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t(ToolI *last_tool_, const color_t &color_):
last_tool(last_tool_),
color    (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_color(const color_t &color_)
{
    color = color_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_tool(ToolI *tool)
{
    last_tool = tool;
    canvas_t::active_instrument = canvas_t::TOOL;
}

#endif // TOOL_MANAGER_H
