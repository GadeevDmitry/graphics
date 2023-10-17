#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "log.h"
#include "tool.h"

//==================================================================================================

class tool_manager_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    tool_t *active_tool;
    color_t color;

public:
    inline          tool_manager_t();
    inline explicit tool_manager_t(tool_t *active_tool_, const color_t &color_);
    inline         ~tool_manager_t() {}

    inline void set_color(const color_t &color_);
    inline void set_tool (tool_t *active_tool_);

    inline void paint_on_mouse_press  (canvas_t &canvas, const MOUSE_BUTTON_TYPE &btn);
    inline void paint_on_mouse_release(canvas_t &canvas, const MOUSE_BUTTON_TYPE &btn);
    inline void paint_on_mouse_move   (canvas_t &canvas, const vec2d             &off);
};

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t():
active_tool(nullptr),
color      ()
{}

//--------------------------------------------------------------------------------------------------

inline tool_manager_t::tool_manager_t(tool_t *active_tool_, const color_t &color_):
active_tool(active_tool_),
color      (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_color(const color_t &color_)
{
    color = color_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::set_tool(tool_t *active_tool_)
{
    active_tool = active_tool_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_press(canvas_t &canvas, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active_tool != nullptr, (void) 0);

    LOG_TAB_MESSAGE("TOOL_MANAGER_T::PAINT_ON_MOUSE_PRESS\n");
    LOG_TAB_MESSAGE("ACTIVE_TOOL = %p\n", active_tool);
    active_tool->paint_on_mouse_press(canvas.perm, canvas.temp, color, canvas.visible.region.ld_corner, btn);
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_release(canvas_t &canvas, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active_tool != nullptr, (void) 0);

    LOG_TAB_MESSAGE("TOOL_MANAGER_T::PAINT_ON_MOUSE_RELEASE\n");
    LOG_TAB_MESSAGE("ACTIVE_TOOL = %p\n", active_tool);
    active_tool->paint_on_mouse_release(canvas.perm, canvas.temp, color, canvas.visible.region.ld_corner, btn);
}

//--------------------------------------------------------------------------------------------------

inline void tool_manager_t::paint_on_mouse_move(canvas_t &canvas, const vec2d &off)
{
    LOG_VERIFY(active_tool != nullptr, (void) 0);

    LOG_TAB_MESSAGE("TOOL_MANAGER_T::PAINT_ON_MOUSE_MOVE\n");
    LOG_TAB_MESSAGE("ACTIVE_TOOL = %p\n", active_tool);
    active_tool->paint_on_mouse_move(canvas.perm, canvas.temp, color, canvas.visible.region.ld_corner, off);
}

#endif // TOOL_MANAGER_H
