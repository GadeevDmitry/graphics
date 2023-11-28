#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

#include "Event.h"
#include "Render.h"
#include "Interface.h"

//==================================================================================================

namespace plugin
{
    struct ToolI: public Interface
    {
        virtual const Texture *get_icon() = 0;

        virtual void paint_on_press  (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) = 0;
        virtual void paint_on_release(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) = 0;
        virtual void paint_on_move   (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) = 0;
        virtual void deactivate      (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) = 0;
    };

    struct ToolManagerI
    {
        virtual void   set_color(Color color) = 0;
        virtual void   set_tool (ToolI *tool) = 0;

        virtual ToolI *get_tool ()            = 0;
        virtual Color  get_color()            = 0;

        virtual void paint_on_move   (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) = 0;
        virtual void paint_on_press  (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) = 0;
        virtual void paint_on_release(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) = 0;
        virtual void disable_tool    (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context) = 0;
    };
}

#endif // PLUGIN_TOOL_H
