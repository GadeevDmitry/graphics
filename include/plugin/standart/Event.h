#ifndef PLUGIN_EVENT_H
#define PLUGIN_EVENT_H

#include <cinttypes>
#include "geometry/vec2d.h"
#include "event/eventable.h"

//==================================================================================================

namespace plugin
{
    enum class Key
    {
        Unknown = -1,
        A = 0,
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
        LControl,
        LShift,
        LAlt,
        LSystem,
        RControl,
        RShift,
        RAlt,
        RSystem,
        Menu,
        LBracket,
        RBracket,
        Semicolon,
        Comma,
        Period,
        Apostrophe,
        Slash,
        Backslash,
        Grave,
        Equal,
        Hyphen,
        Space,
        Enter,
        Backspace,
        Tab,
        PageUp,
        PageDown,
        End,
        Home,
        Insert,
        Delete,
        Add,
        Subtract,
        Multiply,
        Divide,
        Left,
        Right,
        Up,
        Down,
        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        Pause,

        KeyCount,
    };

    struct KeyboardContext
    {
    // static
    public:
        static inline Key      convert_host_key(const KEY_TYPE &host_key);
        static inline KEY_TYPE     get_host_key(const Key      &plugin_key);

    // member functions
    public:
        explicit inline KeyboardContext();
        explicit inline KeyboardContext(const bool alt, const bool shift, const bool ctrl, const Key key);
        explicit inline KeyboardContext(const eventable::key_context_t &context, const KEY_TYPE &key);

    // member data
    public:
        bool alt;
        bool shift;
        bool ctrl;

        Key  key;
    };

    //--------------------------------------------------------------------------------------------------

    inline Key KeyboardContext::convert_host_key(const KEY_TYPE &host_key)
    {
        return (Key) host_key;
    }

    //--------------------------------------------------------------------------------------------------

    inline KEY_TYPE KeyboardContext::get_host_key(const Key &plugin_key)
    {
        if (plugin_key > Key::RSystem) return KEY_TYPE_UNKNOWN;
        return (KEY_TYPE) plugin_key;
    }

    //--------------------------------------------------------------------------------------------------

    inline KeyboardContext::KeyboardContext():
    alt  (false),
    shift(false),
    ctrl (false),
    key  (Key::Unknown)
    {}

    //--------------------------------------------------------------------------------------------------

    inline KeyboardContext::KeyboardContext(const bool alt_, const bool shift_, const bool ctrl_, const Key key_):
    alt  (alt_),
    shift(shift_),
    ctrl (ctrl_),
    key  (key_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline KeyboardContext::KeyboardContext(const eventable::key_context_t &context, const KEY_TYPE &key_):
    alt  (context.alt),
    shift(context.shift),
    ctrl (context.control),
    key  (convert_host_key(key_))
    {}

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    enum class MouseButton
    {
        Left,
        Right
    };

    struct MouseContext
    {
    // static
    public:
        static MouseButton       convert_host_btn(const MOUSE_BUTTON_TYPE &host_btn);
        static MOUSE_BUTTON_TYPE     get_host_btn(const MouseButton       &plugin_btn);

    // member functions
    public:
        explicit inline MouseContext();
        explicit inline MouseContext(const vec2d &position, const MouseButton button);
        explicit inline MouseContext(const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn);
        explicit inline MouseContext(const eventable::mouse_context_t &context, const vec2d             &off);

    // member data
    public:
        vec2d     position;
        MouseButton button;
    };

    //--------------------------------------------------------------------------------------------------

    inline MouseContext::MouseContext():
    position(),
    button  (MouseButton::Left)
    {}

    //--------------------------------------------------------------------------------------------------

    inline MouseContext::MouseContext(const vec2d &position_, const MouseButton button_):
    position(position_),
    button  (button_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline MouseContext::MouseContext(const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn):
    position(context.pos),
    button  (convert_host_btn(btn))
    {}

    //--------------------------------------------------------------------------------------------------

    inline MouseContext::MouseContext(const eventable::mouse_context_t &context, const vec2d &off):
    position(context.pos),
    button  (MouseButton::Left)
    {
        (void) off;
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    enum class EventType
    {
        MousePress,
        MouseRelease,
        MouseMove,
        KeyPress,
        KeyRelease,
	    Clock,

        NumOfEvents
    };

    struct EventProcessableI
    {
        virtual bool on_mouse_move   (MouseContext    context) = 0;
        virtual bool on_mouse_release(MouseContext    context) = 0;
        virtual bool on_mouse_press  (MouseContext    context) = 0;
        virtual bool on_key_press    (KeyboardContext context) = 0;
        virtual bool on_key_release  (KeyboardContext context) = 0;
        virtual bool on_clock        (uint64_t delta)          = 0;

	    virtual uint8_t get_priority() = 0;
    };

    struct EventManagerI
    {
    // static
    public:
        static EventType             convert_host_event(const eventable::EVENT_TYPE &host_event);
        static eventable::EVENT_TYPE     get_host_event(const EventType             &plugin_event);

    // virtual
    public:
        virtual void register_object  (EventProcessableI *object)   = 0;
        virtual void set_priority     (EventType, uint8_t priority) = 0;
        virtual void unregister_object(EventProcessableI *object)   = 0;
    };
}

#endif // PLUGIN_EVENT_H
