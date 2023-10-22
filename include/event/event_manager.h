#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "eventable.h"
#include "data_structs/include/list.h"

//==================================================================================================

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
    inline  event_manager_t();
    inline ~event_manager_t();

    bool inline register_child             (eventable *child);

    bool        process_key_press_event    (const KEY_TYPE          &key);
    bool        process_key_release_event  (const KEY_TYPE          &key);
    bool        process_mouse_press_event  (const MOUSE_BUTTON_TYPE &btn);
    bool        process_mouse_release_event(const MOUSE_BUTTON_TYPE &btn);
    bool        process_mouse_move_event   (const vec2d             &pos);

// member data
protected:
    list childs;
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

inline event_manager_t::event_manager_t()
{
    list_ctor(&childs, sizeof(eventable *), nullptr);
}

//--------------------------------------------------------------------------------------------------

inline event_manager_t::~event_manager_t()
{
    list_dtor(&childs);
}

//--------------------------------------------------------------------------------------------------

inline bool event_manager_t::register_child(eventable *child)
{
    return list_push_back(&childs, &child);
}

#endif // EVENT_MANAGER_H
