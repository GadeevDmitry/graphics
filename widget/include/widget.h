#ifndef WIDGET_H
#define WIDGET_H

#include "renderable.h"

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

struct key_context_t
{
public:
    KEY_TYPE key;
    char     alt;
    char     control;
    char     shift;
    char     system;

    inline          key_context_t();
    inline explicit key_context_t(const KEY_TYPE key_, const char alt_, const char control_, const char shift_, const char system_);
    inline         ~key_context_t() {}

    static KEY_TYPE convert_sfml(const sf::Keyboard::Key &sfml_key);
};

//--------------------------------------------------------------------------------------------------

inline key_context_t::key_context_t():
key    (KEY_TYPE_UNKNOWN),
alt    (false),
control(false),
shift  (false),
system (false)
{}

//--------------------------------------------------------------------------------------------------

inline key_context_t::key_context_t(const KEY_TYPE key_, const char alt_, const char control_, const char shift_, const char system_):
key    (key_),
alt    (alt_),
control(control_),
shift  (shift_),
system (system_)
{}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum MOUSE_BUTTON_TYPE
{
    MOUSE_BUTTON_TYPE_UNKNOWN = -1,

    Left,
    Right,
    Middle,

    MOUSE_BUTTON_TYPE_COUNT,
};

//--------------------------------------------------------------------------------------------------

struct mouse_context_t
{
public:
    vec2d pos;
    char  left;
    char  right;
    char  middle;

    inline  mouse_context_t();
    inline ~mouse_context_t() {}

    static MOUSE_BUTTON_TYPE convert_sfml(const sf::Mouse::Button &sfml_mouse_btn);
};

//--------------------------------------------------------------------------------------------------

inline mouse_context_t::mouse_context_t():
pos   (),
left  (false),
right (false),
middle(false)
{}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class widget_manager_t;
class button_t;
class menu_t;

class widget_t: public renderable
{
///////////////////////////////////////////////
// TYPES
///////////////////////////////////////////////
public:

    enum WIDGET_STATUS_TYPE
    {
        WIDGET_OPENED,
        WIDGET_CLOSED,
    };

protected:
    typedef bool (widget_t::*on_key_click_event)   (const KEY_TYPE          &key);
    typedef bool (widget_t::*on_mouse_click_event) (const MOUSE_BUTTON_TYPE &btn);

///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
private:
    static key_context_t   saved_key_context;
    static mouse_context_t saved_mouse_context;

    static bool  refresh_context_on_key_press    (const KEY_TYPE          &pressed_key);
    static bool  refresh_context_on_key_release  (const KEY_TYPE          &released_key);
    static bool  refresh_context_on_mouse_press  (const MOUSE_BUTTON_TYPE &pressed_btn);
    static bool  refresh_context_on_mouse_release(const MOUSE_BUTTON_TYPE &released_btn);
    static vec2d refresh_context_on_mouse_move   (const sf::Vector2i      &pos);

protected:
    static widget_t *active;

public:
    static bool process_key_press_event    (widget_t &system, const KEY_TYPE          &pressed_key);
    static bool process_key_release_event  (widget_t &system, const KEY_TYPE          &released_key);
    static bool process_mouse_press_event  (widget_t &system, const MOUSE_BUTTON_TYPE &pressed_btn);
    static bool process_mouse_release_event(widget_t &system, const MOUSE_BUTTON_TYPE &released_btn);
    static bool process_mouse_move_event   (widget_t &system, const sf::Vector2i      &pos);

    static inline const mouse_context_t &get_mouse_context();
    static inline const key_context_t   &get_key_context  ();
    static inline void                   widget_delete    (void *const widget_);

///////////////////////////////////////////////
// FRIENDS
///////////////////////////////////////////////
public:
    friend widget_manager_t;
    friend button_t;
    friend menu_t;

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    inline          widget_t();
    inline explicit widget_t(const rectangle_t &region_);

    virtual void move(const vec2d &offset) = 0;

    virtual rectangle_t  get_region() const = 0;
    virtual void        dump_region() const {} ;

    virtual bool on_key_press    (const KEY_TYPE          &key) = 0;
    virtual bool on_key_release  (const KEY_TYPE          &key) = 0;
    virtual bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual bool on_mouse_move   (const vec2d             &off) = 0;

    virtual void recalc_region() override {}

protected:
    WIDGET_STATUS_TYPE status;
};  

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t():
status(WIDGET_OPENED)
{}

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t(const rectangle_t &region_):
renderable(region_),
status    (WIDGET_OPENED)
{}

//--------------------------------------------------------------------------------------------------

inline void widget_t::widget_delete(void *const widget_)
{
    widget_t *widget = *(widget_t **) widget_;
    delete    widget;
}

//--------------------------------------------------------------------------------------------------

const mouse_context_t &widget_t::get_mouse_context()
{
    return saved_mouse_context;
}

//--------------------------------------------------------------------------------------------------

const key_context_t &widget_t::get_key_context()
{
    return saved_key_context;
}

#endif // WIDGET_H
