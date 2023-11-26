#ifndef PLUGIN_HOST_EVENT_MANAGER_I_H
#define PLUGIN_HOST_EVENT_MANAGER_I_H

#include "plugin/standart/Event.h"
#include "event/event_manager.h"

//==================================================================================================

using plugin::EventProcessableI;
using plugin::EventType;

namespace host
{
    class HostEventManagerI: public plugin::EventManagerI
    {
    // member functions
    public:
        explicit inline HostEventManagerI(event_manager_t &event_manager);

    // virtual
    public:
        virtual void register_object  (EventProcessableI *object)        override;
        virtual void set_priority     (EventType type, uint8_t priority) override;
        virtual void unregister_object(EventProcessableI *object)        override;

    // member data
    private:
        event_manager_t &event_manager;
    };

    //--------------------------------------------------------------------------------------------------

    inline HostEventManagerI::HostEventManagerI(event_manager_t &event_manager_):
    event_manager(event_manager_)
    {}
}

#endif // PLUGIN_HOST_EVENT_MANAGER_I_H
