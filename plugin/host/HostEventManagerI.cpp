#include <stdio.h>

#include "host/HostEventManagerI.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

namespace host
{
    void HostEventManagerI::register_object(EventProcessableI *object)
    {
        event_manager.register_child(eventable_proxy(object));
    }

    //--------------------------------------------------------------------------------------------------

    void HostEventManagerI::set_priority(EventType plugin_event, uint8_t priority)
    {
        eventable::EVENT_TYPE host_event = plugin::EventManagerI::get_host_event(plugin_event);
        if (host_event == eventable::EVENT_TYPE_UNKNOWN) return;

        event_manager.set_event_priority(priority, host_event);
    }

    //--------------------------------------------------------------------------------------------------

    void HostEventManagerI::unregister_object(EventProcessableI *object)
    {
        if (!event_manager.unregister_child(eventable_proxy(object)))
            LOG_ERROR("attempt to delete an unregistered object\n");
    }
}
