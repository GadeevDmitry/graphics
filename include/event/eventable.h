#ifndef EVENTABLE_H
#define EVENTABLE_H

#include "geometry/vec2d.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

enum KEY_TYPE
{
    KEY_TYPE_UNKNOWN = -1,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Escape,

    //>>> special keys
    LControl,
    LShift,
    LAlt,
    LSystem,
    RControl,
    RShift,
    RAlt,
    RSystem,
    //<<< special keys

    KEY_TYPE_COUNT,
};

//--------------------------------------------------------------------------------------------------

enum MOUSE_BUTTON_TYPE
{
    MOUSE_BUTTON_TYPE_UNKNOWN = -1,

    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,

    MOUSE_BUTTON_TYPE_COUNT,
};

//==================================================================================================

class event_manager_t;

class eventable
{
// types
public:
    struct key_context_t
    {
        static KEY_TYPE convert_sfml_key(const sf::Keyboard::Key &sfml_key);

        KEY_TYPE key;
        char     alt;
        char     control;
        char     shift;
        char     system;

        inline  key_context_t();
        inline ~key_context_t() {}
    };

    struct mouse_context_t
    {
        static MOUSE_BUTTON_TYPE convert_sfml_btn(const sf::Mouse::Button &sfml_mouse_btn);
        static vec2d             convert_sfml_pos(const sf::Vector2i      &sfml_mouse_pos);

        vec2d pos;
        char  left;
        char  right;
        char  middle;

        inline  mouse_context_t();
        inline ~mouse_context_t() {}
    };

    enum EVENT_TYPE
    {
        EVENT_TYPE_UNKNOWN = -1,

        EVENT_KEY_PRESS     ,
        EVENT_KEY_RELEASE   ,
        EVENT_MOUSE_PRESS   ,
        EVENT_MOUSE_RELEASE ,
        EVENT_MOUSE_MOVE    ,

        EVENT_TYPE_COUNT,
    };

// member functions
public:
             inline  eventable();
    explicit inline  eventable(const unsigned char event_priority);
    virtual  inline ~eventable() {}

// virtual
public:
    virtual bool on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) = 0;
    virtual bool on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) = 0;
    virtual bool on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual bool on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual bool on_mouse_move   (const mouse_context_t &context, const vec2d             &off) = 0;

// member data
public:
    unsigned char event_priority;

// friends
    friend event_manager_t;
};

//--------------------------------------------------------------------------------------------------

inline eventable::key_context_t::key_context_t():
key    (KEY_TYPE_UNKNOWN),
alt    (false),
control(false),
shift  (false),
system (false)
{}

//--------------------------------------------------------------------------------------------------

inline eventable::mouse_context_t::mouse_context_t():
pos   (),
left  (false),
right (false),
middle(false)
{}

//--------------------------------------------------------------------------------------------------

inline eventable::eventable():
event_priority(0)
{}

//--------------------------------------------------------------------------------------------------

inline eventable::eventable(const unsigned char event_priority_):
event_priority(event_priority_)
{}

#endif // EVENTABLE_H
