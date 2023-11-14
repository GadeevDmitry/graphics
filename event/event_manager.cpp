#include <stdio.h>
#include "event_manager.h"
#include "data_structs/include/log.h"

//==================================================================================================

eventable::key_context_t   event_manager_t::global_key_context;
eventable::mouse_context_t event_manager_t::global_mouse_context;

//==================================================================================================

event_manager_t::event_manager_t()
{
    list_ctor(&childs, sizeof(eventable *), nullptr);

    unsigned char init_value = 0;
    array_ctor(&pass_priorities, eventable::EVENT_TYPE_COUNT, sizeof(unsigned char));
    array_init(&pass_priorities, &init_value);
}

//--------------------------------------------------------------------------------------------------

event_manager_t::~event_manager_t()
{
    list_dtor (&childs);
    array_dtor(&pass_priorities);
}

//--------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"

bool event_manager_t::refresh_context_on_key_press(const KEY_TYPE &pressed_key)
{
    if (pressed_key == KEY_TYPE_UNKNOWN)
        return false;

    if (pressed_key >= LControl && pressed_key <= RSystem)
    {
        switch (pressed_key)
        {
            case LControl:
            case RControl: global_key_context.control = true; break;

            case LAlt    :
            case RAlt    : global_key_context.alt     = true; break;

            case LShift  :
            case RShift  : global_key_context.shift   = true; break;

            case LSystem :
            case RSystem : global_key_context.system  = true; break;

            default: break;
        }

        return false;
    }

    if (global_key_context.key != KEY_TYPE_UNKNOWN)
        return false;

    global_key_context.key = pressed_key;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::refresh_context_on_key_release(const KEY_TYPE &released_key)
{

    if (released_key == KEY_TYPE_UNKNOWN)
        return false;

    if (released_key >= LControl && released_key <= RSystem)
    {
        switch (released_key)
        {
            case LControl:
            case RControl: global_key_context.control = false; break;

            case LAlt    :
            case RAlt    : global_key_context.alt     = false; break;

            case LShift  :
            case RShift  : global_key_context.shift   = false; break;

            case LSystem :
            case RSystem : global_key_context.system  = false; break;

            default: break;
        }
    }

    if (global_key_context.key != released_key)
        return false;

    global_key_context.key = KEY_TYPE_UNKNOWN;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::refresh_context_on_mouse_press(const MOUSE_BUTTON_TYPE &pressed_btn)
{
    if (pressed_btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        return false;

    switch (pressed_btn)
    {
        case MOUSE_BUTTON_LEFT  : global_mouse_context.left   = true; break;
        case MOUSE_BUTTON_RIGHT : global_mouse_context.right  = true; break;
        case MOUSE_BUTTON_MIDDLE: global_mouse_context.middle = true; break;

        default: break;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::refresh_context_on_mouse_release(const MOUSE_BUTTON_TYPE &released_btn)
{
    if (released_btn == MOUSE_BUTTON_TYPE_UNKNOWN)
        return false;

    switch (released_btn)
    {
        case MOUSE_BUTTON_LEFT  : global_mouse_context.left   = false; break;
        case MOUSE_BUTTON_RIGHT : global_mouse_context.right  = false; break;
        case MOUSE_BUTTON_MIDDLE: global_mouse_context.middle = false; break;

        default: break;
    }

    return true;
}

#pragma GCC diagnostic pop

//--------------------------------------------------------------------------------------------------

vec2d event_manager_t::refresh_context_on_mouse_move(const vec2d &mouse_pos)
{
    vec2d offset = mouse_pos - global_mouse_context.pos;
    global_mouse_context.pos = mouse_pos;
    return offset;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::process_key_press_event(const KEY_TYPE &key)
{
    if (!refresh_context_on_key_press(key)) return false;

    eventable::key_context_t local_context = global_key_context;
    bool res = false;

    eventable **child = (eventable **) list_front(&childs);
    eventable **fict  = (eventable **) list_fict (&childs);

    for (; child != fict; child = (eventable **) list_next(child))
    {
        unsigned char pass_priority = *(unsigned char *) array_get(&pass_priorities, eventable::EVENT_KEY_PRESS);

        if ((**child).event_priority < pass_priority) continue;
        if ((**child).on_key_press(local_context, key)) res = true;
    }

    return res;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::process_key_release_event(const KEY_TYPE &key)
{
    if (!refresh_context_on_key_release(key)) return false;

    eventable::key_context_t local_context = global_key_context;
    bool res = false;

    eventable **child = (eventable **) list_front(&childs);
    eventable **fict  = (eventable **) list_fict (&childs);

    for (; child != fict; child = (eventable **) list_next(child))
    {
        unsigned char pass_priority = *(unsigned char *) array_get(&pass_priorities, eventable::EVENT_KEY_RELEASE);

        if ((**child).event_priority < pass_priority) continue;
        if ((**child).on_key_release(local_context, key)) res = true;
    }

    return res;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::process_mouse_press_event(const MOUSE_BUTTON_TYPE &btn)
{
    if (!refresh_context_on_mouse_press(btn)) return false;

    eventable::mouse_context_t local_context = global_mouse_context;
    bool res = false;

    eventable **child = (eventable **) list_front(&childs);
    eventable **fict  = (eventable **) list_fict (&childs);

    for (; child != fict; child = (eventable **) list_next(child))
    {
        unsigned char pass_priority = *(unsigned char *) array_get(&pass_priorities, eventable::EVENT_MOUSE_PRESS);

        if ((**child).event_priority < pass_priority) continue;
        if ((**child).on_mouse_press(local_context, btn)) res = true;
    }

    return res;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::process_mouse_release_event(const MOUSE_BUTTON_TYPE &btn)
{
    if (!refresh_context_on_mouse_release(btn)) return false;

    eventable::mouse_context_t local_context = global_mouse_context;
    bool res = false;

    eventable **child = (eventable **) list_front(&childs);
    eventable **fict  = (eventable **) list_fict (&childs);

    for (; child != fict; child = (eventable **) list_next(child))
    {
        unsigned char pass_priority = *(unsigned char *) array_get(&pass_priorities, eventable::EVENT_MOUSE_RELEASE);

        if ((**child).event_priority < pass_priority) continue;
        if ((**child).on_mouse_release(local_context, btn)) res = true;
    }

    return res;
}

//--------------------------------------------------------------------------------------------------

bool event_manager_t::process_mouse_move_event(const vec2d &pos)
{
    vec2d off = refresh_context_on_mouse_move(pos);

    eventable::mouse_context_t local_context = global_mouse_context;
    bool res = false;

    eventable **child = (eventable **) list_front(&childs);
    eventable **fict  = (eventable **) list_fict (&childs);

    for (; child != fict; child = (eventable **) list_next(child))
    {
        unsigned char pass_priority = *(unsigned char *) array_get(&pass_priorities, eventable::EVENT_MOUSE_MOVE);

        if ((**child).event_priority < pass_priority) continue;
        if ((**child).on_mouse_move(local_context, off)) res = true;
    }

    return res;
}
