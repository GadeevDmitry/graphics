#ifndef PLUGIN_HOST_GUI_I_H
#define PLUGIN_HOST_GUI_I_H

#include "widget/widget_container.h"
#include "plugin/host/HostWidgetI.h"
#include "plugin/standart/application.h"

//==================================================================================================

using plugin::RenderTargetI;
using plugin::Interface;
using plugin::Array;
using plugin::Plugin;

namespace host
{
    class HostGuiI: public plugin::GuiI
    {
    // member functions
    public:
        explicit inline HostGuiI(widget_container_t &root);

    // virtual
    public:
        virtual vec2d          get_size           ()                                                  override;
        virtual RenderTargetI *get_render_target  (vec2d size, vec2d pos          , Plugin    *self) override;
        virtual void           create_param_window(Array<const char *> param_names, Interface *self) override;
        virtual WidgetI       *get_root           ()                                                  override;

    // member data
    private:
        widget_container_t &internal_root;
        HostWidgetI         external_root;
    };

    //--------------------------------------------------------------------------------------------------

    inline HostGuiI::HostGuiI(widget_container_t &root_):
    internal_root(root_),
    external_root(root_)
    {}
}

#endif // PLUGIN_HOST_GUI_I_H
