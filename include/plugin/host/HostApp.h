#ifndef PLUGIN_HOST_APP_H
#define PLUGIN_HOST_APP_H

#include "plugin/standart/application.h"

#include "plugin/host/HostGuiI.h"
#include "plugin/host/HostToolManagerI.h"
#include "plugin/host/HostEventManagerI.h"
#include "plugin/host/HostFilterManagerI.h"

//==================================================================================================

namespace host
{
    class HostApp: public plugin::App
    {
    // member functions
    public:
        inline  HostApp();
        inline ~HostApp();

        void inline create(widget_container_t &root, event_manager_t &event_manager, tool_manager_t &tool_manager , filter_manager_t &filter_manager);
    };

    //--------------------------------------------------------------------------------------------------

    inline HostApp::HostApp():
    plugin::App()
    {}

    //--------------------------------------------------------------------------------------------------

    inline HostApp::~HostApp()
    {
        delete (HostGuiI           *) root;
        delete (HostEventManagerI  *) event_manager;
        delete (HostToolManagerI   *) tool_manager;
        delete (HostFilterManagerI *) filter_manager;
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostApp::create(widget_container_t &root_, event_manager_t &event_manager_, tool_manager_t &tool_manager_, filter_manager_t &filter_manager_)
    {
        root           = new HostGuiI(root_);
        event_manager  = new HostEventManagerI (event_manager_);
        tool_manager   = new HostToolManagerI  (tool_manager_);
        filter_manager = new HostFilterManagerI(filter_manager_);
    }
}

#endif // PLUGIN_HOST_APP_H
