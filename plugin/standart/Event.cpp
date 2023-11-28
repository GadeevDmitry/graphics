#include <stdio.h>
#include "standart/Event.h"
#include "data_structs/include/log.h"

//==================================================================================================

namespace plugin
{
    MouseButton MouseContext::convert_host_btn(const MOUSE_BUTTON_TYPE &host_btn)
    {
        switch (host_btn)
        {
            case MOUSE_BUTTON_LEFT : return MouseButton::Left;
            case MOUSE_BUTTON_RIGHT: return MouseButton::Right;

            default                : return MouseButton::Left /* MouseButton::Unknown */;
        }

        return MouseButton::Left;
    }

    //--------------------------------------------------------------------------------------------------

    MOUSE_BUTTON_TYPE MouseContext::get_host_btn(const MouseButton &plugin_btn)
    {
        switch (plugin_btn)
        {
            case MouseButton::Left : return MOUSE_BUTTON_LEFT;
            case MouseButton::Right: return MOUSE_BUTTON_RIGHT;

            default                : LOG_ERROR("undefined plugin::MouseContext value\n");
                                     return MOUSE_BUTTON_TYPE_UNKNOWN;
        }

        return MOUSE_BUTTON_TYPE_UNKNOWN;
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    EventType EventManagerI::convert_host_event(const eventable::EVENT_TYPE &host_event)
    {
        switch (host_event)
        {
            case eventable::EVENT_KEY_PRESS    : return EventType::KeyPress;
            case eventable::EVENT_KEY_RELEASE  : return EventType::KeyRelease;
            case eventable::EVENT_MOUSE_PRESS  : return EventType::MousePress;
            case eventable::EVENT_MOUSE_RELEASE: return EventType::MouseRelease;
            case eventable::EVENT_MOUSE_MOVE   : return EventType::MouseMove;

            default                            : return EventType::NumOfEvents /* EventType::Unknown */;
        }

        return EventType::NumOfEvents;
    }

    //--------------------------------------------------------------------------------------------------

    eventable::EVENT_TYPE EventManagerI::get_host_event(const EventType &plugin_event)
    {
        switch (plugin_event)
        {
            case EventType::MousePress  : return eventable::EVENT_MOUSE_PRESS;
            case EventType::MouseRelease: return eventable::EVENT_MOUSE_RELEASE;
            case EventType::MouseMove   : return eventable::EVENT_MOUSE_MOVE;
            case EventType::KeyPress    : return eventable::EVENT_KEY_PRESS;
            case EventType::KeyRelease  : return eventable::EVENT_KEY_RELEASE;

            case EventType::Clock       : LOG_WARNING("Clock events are not supported by application\n");
            default                     : return eventable::EVENT_TYPE_UNKNOWN;
        }
        return eventable::EVENT_TYPE_UNKNOWN;
    }
}
