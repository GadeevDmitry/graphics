#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "eventable_proxy.h"
#include "data_structs/include/log.h"
#include "data_structs/include/list.h"
#include "data_structs/include/array.h"

//==================================================================================================

namespace host
{
    class HostEventManagerI;
}

class event_manager_t
{
// static
public:
    static const eventable::key_context_t   inline &get_global_key_context  ();
    static const eventable::mouse_context_t inline &get_global_mouse_context();

private:
    static eventable::key_context_t   global_key_context;
    static eventable::mouse_context_t global_mouse_context;

    static bool  refresh_context_on_key_press    (const KEY_TYPE          &pressed_key);
    static bool  refresh_context_on_key_release  (const KEY_TYPE          &released_key);
    static bool  refresh_context_on_mouse_press  (const MOUSE_BUTTON_TYPE &pressed_btn);
    static bool  refresh_context_on_mouse_release(const MOUSE_BUTTON_TYPE &released_btn);
    static vec2d refresh_context_on_mouse_move   (const vec2d             &mouse_pos);

// member functions
public:
     event_manager_t();
    ~event_manager_t();

    bool inline   register_child           (const eventable_proxy &child);
    bool        unregister_child           (const eventable_proxy &child);

    void inline set_all_priorities         (const unsigned char pass_priority);
    void inline set_event_priority         (const unsigned char pass_priority, const eventable::EVENT_TYPE event);

    bool        process_key_press_event    (const KEY_TYPE          &key);
    bool        process_key_release_event  (const KEY_TYPE          &key);
    bool        process_mouse_press_event  (const MOUSE_BUTTON_TYPE &btn);
    bool        process_mouse_release_event(const MOUSE_BUTTON_TYPE &btn);
    bool        process_mouse_move_event   (const vec2d             &pos);

// member data
protected:
    list  childs;
    array pass_priorities;

// friends
    friend host::HostEventManagerI;
};

//--------------------------------------------------------------------------------------------------

inline const eventable::key_context_t &event_manager_t::get_global_key_context()
{
    return global_key_context;
}

//--------------------------------------------------------------------------------------------------

inline const eventable::mouse_context_t &event_manager_t::get_global_mouse_context()
{
    return global_mouse_context;
}

//--------------------------------------------------------------------------------------------------

inline bool event_manager_t::register_child(const eventable_proxy &child)
{
    return list_push_back(&childs, &child);
}

//--------------------------------------------------------------------------------------------------

inline void event_manager_t::set_all_priorities(const unsigned char pass_priority)
{
    array_init(&pass_priorities, &pass_priority);
}

//--------------------------------------------------------------------------------------------------

inline void event_manager_t::set_event_priority(const unsigned char pass_priority, const eventable::EVENT_TYPE event)
{
    LOG_VERIFY(event > eventable::EVENT_TYPE_UNKNOWN, (void) 0);
    LOG_VERIFY(event < eventable::EVENT_TYPE_COUNT  , (void) 0);
    array_set(&pass_priorities, (size_t) event, &pass_priority);
}

#endif // EVENT_MANAGER_H
