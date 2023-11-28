#include <stdio.h>

#include "tool_manager.h"
#include "plugin/host/HostRenderTargetI.h"

#include "data_structs/include/log.h"

//==================================================================================================

void tool_manager_t::paint_on_mouse_press(render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(last_tool != nullptr, (void) 0);

    host::HostRenderTargetI permI(perm);
    host::HostRenderTargetI tempI(temp);

    last_tool->paint_on_press(&permI, &tempI, plugin::MouseContext(local_context, btn), plugin::Color(color));
}

//--------------------------------------------------------------------------------------------------

void tool_manager_t::paint_on_mouse_release(render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(last_tool != nullptr, (void) 0);

    host::HostRenderTargetI permI(perm);
    host::HostRenderTargetI tempI(temp);

    last_tool->paint_on_release(&permI, &tempI, plugin::MouseContext(local_context, btn), plugin::Color(color));
}

//--------------------------------------------------------------------------------------------------

void tool_manager_t::paint_on_mouse_move(render_texture_t &perm, render_texture_t &temp, const eventable::mouse_context_t &local_context, const vec2d &off)
{
    LOG_VERIFY(last_tool != nullptr, (void) 0);

    host::HostRenderTargetI permI(perm);
    host::HostRenderTargetI tempI(temp);

    last_tool->paint_on_move(&permI, &tempI, plugin::MouseContext(local_context, off), plugin::Color(color));
}
