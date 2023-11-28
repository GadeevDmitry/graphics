#ifndef EVENTABLE_PROXY_H
#define EVENTABLE_PROXY_H

#include "eventable.h"
#include "plugin/standart/Event.h"

//==================================================================================================

using plugin::EventProcessableI;

class eventable_proxy
{
// static
public:
    static void inline eventable_proxy_dtor(void *eventable_proxy_object);

// member functions
public:
    explicit inline  eventable_proxy(eventable         *internal);
    explicit inline  eventable_proxy(EventProcessableI *external);
             inline ~eventable_proxy() {}

    bool on_key_press    (const eventable::key_context_t   &context, const KEY_TYPE          &key) const;
    bool on_key_release  (const eventable::key_context_t   &context, const KEY_TYPE          &key) const;
    bool on_mouse_press  (const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) const;
    bool on_mouse_release(const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) const;
    bool on_mouse_move   (const eventable::mouse_context_t &context, const vec2d             &off) const;

    unsigned char inline get_priority() const;

// member data
public:
    const bool is_internal;

    union
    {
        eventable         *internal;
        EventProcessableI *external;
    };
};

//--------------------------------------------------------------------------------------------------

inline void eventable_proxy::eventable_proxy_dtor(void *eventable_proxy_object)
{
    ((eventable_proxy *) eventable_proxy_object)->~eventable_proxy();
}

//--------------------------------------------------------------------------------------------------

inline eventable_proxy::eventable_proxy(eventable *internal_):
is_internal(true),
internal   (internal_)
{}

//--------------------------------------------------------------------------------------------------

inline eventable_proxy::eventable_proxy(EventProcessableI *external_):
is_internal(false),
external   (external_)
{}

//--------------------------------------------------------------------------------------------------

inline unsigned char eventable_proxy::get_priority() const
{
    if (is_internal) return internal->event_priority;
    return (unsigned char) external->get_priority();
}

#endif // EVENTABLE_PROXY_H
