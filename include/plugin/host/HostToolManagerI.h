#ifndef PLUGIN_HOST_TOOL_MANAGER_I_H
#define PLUGIN_HOST_TOOL_MANAGER_I_H

#include "plugin/standart/Tool.h"
#include "tool/tool_manager.h"

//==================================================================================================

using plugin::ToolI;
using plugin::Color;
using plugin::MouseContext;
using plugin::RenderTargetI;

namespace host
{
    class HostToolManagerI: public plugin::ToolManagerI
    {
    // member functions
    public:
        explicit inline HostToolManagerI(tool_manager_t &tool_manager);

    // virtual
    public:
        virtual void  inline  set_color(Color color) override;
        virtual void  inline  set_tool (ToolI *tool) override;

        virtual ToolI inline *get_tool ()            override;
        virtual Color inline  get_color()            override;

        virtual void  inline  paint_on_move   (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) override;
        virtual void  inline  paint_on_press  (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) override;
        virtual void  inline  paint_on_release(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) override;
        virtual void  inline  disable_tool    (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) override;

    // member data
    private:
        tool_manager_t &tool_manager;
    };

    //--------------------------------------------------------------------------------------------------

    inline HostToolManagerI::HostToolManagerI(tool_manager_t &tool_manager_):
    tool_manager(tool_manager_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline void HostToolManagerI::set_color(Color color)
    {
        tool_manager.set_color(color.get_host_color());
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostToolManagerI::set_tool(ToolI *tool)
    {
        tool_manager.set_tool(tool);
    }

    //--------------------------------------------------------------------------------------------------

    inline ToolI *HostToolManagerI::get_tool()
    {
        return tool_manager.last_tool;
    }

    //--------------------------------------------------------------------------------------------------

    inline Color HostToolManagerI::get_color()
    {
        return Color(tool_manager.color);
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostToolManagerI::paint_on_press(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context)
    {
        LOG_VERIFY(tool_manager.last_tool != nullptr, (void) 0);
        tool_manager.last_tool->paint_on_press(perm, temp, local_context, Color(tool_manager.color));
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostToolManagerI::paint_on_release(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context)
    {
        LOG_VERIFY(tool_manager.last_tool != nullptr, (void) 0);
        tool_manager.last_tool->paint_on_release(perm, temp, local_context, Color(tool_manager.color));
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostToolManagerI::paint_on_move(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context)
    {
        LOG_VERIFY(tool_manager.last_tool != nullptr, (void) 0);
        tool_manager.last_tool->paint_on_move(perm, temp, local_context, Color(tool_manager.color));
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostToolManagerI::disable_tool(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context)
    {
        LOG_VERIFY(tool_manager.last_tool != nullptr, (void) 0);
        tool_manager.last_tool->deactivate(perm, temp, local_context, Color(tool_manager.color));
    }
}

#endif // PLUGIN_HOST_TOOL_MANAGER_I_H
