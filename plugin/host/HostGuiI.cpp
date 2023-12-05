#include <stdio.h>

#include "host/HostGuiI.h"
#include "data_structs/include/log.h"

//==================================================================================================

namespace host
{
    vec2d HostGuiI::get_size()
    {
        return internal_root.enclosing.get_size();
    }

    //--------------------------------------------------------------------------------------------------

    RenderTargetI *HostGuiI::get_render_target(vec2d size, vec2d pos, Plugin *self)
    {
        LOG_ERROR("HostGuiI::get_render_target is not available for plugin\n");
        return nullptr;
    }

    //--------------------------------------------------------------------------------------------------

    void HostGuiI::create_param_window(Array<const char *> param_names, Interface *self)
    {
        LOG_ERROR("HostGuiI::create_param_window is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    WidgetI *HostGuiI::get_root()
    {
        return &external_root;
    }
}
