#include <stdio.h>

#include "host/HostEventManagerI.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

namespace host
{
    void HostEventManagerI::register_object(EventProcessableI *object)
    {
        eventable_proxy object_proxy = eventable_proxy(object);
        event_manager.register_child(object_proxy);
    }

    //--------------------------------------------------------------------------------------------------

    void HostEventManagerI::set_priority(EventType plugin_type, uint8_t priority)
    {
        eventable::EVENT_TYPE host_type = eventable::EVENT_TYPE_UNKNOWN;
        switch (plugin_type)
        {
            case plugin::EventType::MousePress  : host_type = eventable::EVENT_MOUSE_PRESS  ; break;
            case plugin::EventType::MouseRelease: host_type = eventable::EVENT_MOUSE_RELEASE; break;
            case plugin::EventType::MouseMove   : host_type = eventable::EVENT_MOUSE_MOVE   ; break;
            case plugin::EventType::KeyPress    : host_type = eventable::EVENT_KEY_PRESS    ; break;
            case plugin::EventType::KeyRelease  : host_type = eventable::EVENT_KEY_RELEASE  ; break;

            case plugin::EventType::Clock       : LOG_WARNING("Clock events are not supported\n");

            case plugin::EventType::NumOfEvents :
            default                             : break;
        }

        event_manager.set_event_priority(priority, host_type);
    }

    //--------------------------------------------------------------------------------------------------

    void HostEventManagerI::unregister_object(EventProcessableI *object)
    {
        eventable_proxy *child = (eventable_proxy *) list_front(&event_manager.childs);
        eventable_proxy *fict  = (eventable_proxy *) list_fict (&event_manager.childs);

        for (size_t cnt = 0; child != fict; ++cnt)
        {
            if (!child->is_internal && object == child->external)
            {
                list_erase(&event_manager.childs, cnt);
                return;
            }

            child = (eventable_proxy *) list_next(child);
        }

        LOG_ERROR("attempt to delete an unregistered object\n");
    }
}
