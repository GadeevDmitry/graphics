#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tool.h"
#include "widget/canvas.h"
#include "data_structs/include/log.h"

//==================================================================================================

class tool_manager_t
{
// member functions
public:
             inline  tool_manager_t();
    explicit inline  tool_manager_t(tool_t *last_tool, const color_t &color);
             inline ~tool_manager_t() {}

    void inline set_color             (const color_t &color);
    void inline set_tool              (tool_t *tool);

    void inline paint_on_mouse_press  (render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn);
    void inline paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn);
    void inline paint_on_mouse_move   (render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const vec2d             &off);

// member data
private:
    tool_t *last_tool;
    color_t color;
};

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t():
last_tool(nullptr),
color    ()
{}

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t(tool_t *last_tool_, const color_t &color_):
last_tool(last_tool_),
color    (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_color(const color_t &color_)
{
    color = color_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_tool(tool_t *tool)
{
    last_tool = tool;
    canvas_t::active_instrument = canvas_t::TOOL;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_press(render_texture_t &perm, render_texture_t &temp,
                                                 const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(last_tool != nullptr, (void) 0);
    last_tool->paint_on_mouse_press(perm, temp, color, local_context, btn);
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp,
                                                   const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(last_tool != nullptr, (void) 0);
    last_tool->paint_on_mouse_release(perm, temp, color, local_context, btn);
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_move(render_texture_t &perm, render_texture_t &temp,
                                                const eventable::mouse_context_t &local_context, const vec2d &off)
{
    LOG_VERIFY(last_tool != nullptr, (void) 0);
    last_tool->paint_on_mouse_move(perm, temp, color, local_context, off);
}

#endif // TOOL_MANAGER_H
