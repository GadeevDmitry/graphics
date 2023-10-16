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
///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
public:
    static KEY_TYPE convert_sfml(const sf::Keyboard::Key &sfml_key);

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    KEY_TYPE key;
    char     alt;
    char     control;
    char     shift;
    char     system;

    inline          key_context_t();
    inline explicit key_context_t(const KEY_TYPE key_, const char alt_, const char control_, const char shift_, const char system_);
    inline         ~key_context_t() {}
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
///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
public:
    static MOUSE_BUTTON_TYPE convert_sfml(const sf::Mouse::Button &sfml_mouse_btn);

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    vec2d pos;
    char  left;
    char  right;
    char  middle;

    inline  mouse_context_t();
    inline ~mouse_context_t() {}
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
class window_t;
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
        WIDGET_UPDATED,
    };

protected:
    typedef bool (*widget_key_click_func)   (widget_t *self, void *args, const KEY_TYPE          &key);
    typedef bool (*widget_mouse_click_func) (widget_t *self, void *args, const MOUSE_BUTTON_TYPE &btn);
    typedef bool (*widget_mouse_move_func)  (widget_t *self, void *args, const vec2d             &off);

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

    static bool   activate_by_mouse_click(widget_t *self, void *args, const MOUSE_BUTTON_TYPE &btn);
    static bool deactivate_by_mouse_click(widget_t *self, void *args, const MOUSE_BUTTON_TYPE &btn);
    static bool      close_by_mouse_click(widget_t *self, void *args, const MOUSE_BUTTON_TYPE &btn);
    static bool       move_by_mouse_move (widget_t *self, void *args, const vec2d             &off);

public:
    static bool process_key_press_event    (widget_t &system, const KEY_TYPE          &pressed_key);
    static bool process_key_release_event  (widget_t &system, const KEY_TYPE          &released_key);
    static bool process_mouse_press_event  (widget_t &system, const MOUSE_BUTTON_TYPE &pressed_btn);
    static bool process_mouse_release_event(widget_t &system, const MOUSE_BUTTON_TYPE &released_btn);
    static bool process_mouse_move_event   (widget_t &system, const sf::Vector2i      &pos);

    static inline const mouse_context_t &get_mouse_context();
    static inline const key_context_t   &get_key_context  ();

    static inline void widget_delete(void *const widget_);

///////////////////////////////////////////////
// FRIENDS
///////////////////////////////////////////////
public:
    friend widget_manager_t;
    friend window_t;
    friend button_t;
    friend menu_t;

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    bool refresh();

protected:
    WIDGET_STATUS_TYPE status;
    widget_t          *ancestor;

    inline const rectangle_t &get_region() const;

    void update_ancestral_status(WIDGET_STATUS_TYPE upd_status);

    virtual inline void move(const vec2d &offset);
    virtual inline bool update_struct() { return false; }
    virtual inline void recalc_region() override {}

    virtual bool on_key_press    (const KEY_TYPE          &key) = 0;
    virtual bool on_key_release  (const KEY_TYPE          &key) = 0;
    virtual bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) = 0;
    virtual bool on_mouse_move   (const vec2d             &off) = 0;

public:
    inline          widget_t(widget_t *ancestor_ = nullptr);
    inline explicit widget_t(const rectangle_t &region_, widget_t *ancestor_ = nullptr);

    virtual void dump_region() const override {}
};

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t(widget_t *ancestor_):
status  (WIDGET_OPENED),
ancestor(ancestor_)
{}

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t(const rectangle_t &region_, widget_t *ancestor_):
renderable(region_),
status    (WIDGET_OPENED),
ancestor  (ancestor_)
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

//--------------------------------------------------------------------------------------------------

inline void widget_t::move(const vec2d &offset)
{
    visible.region += offset;
}

//--------------------------------------------------------------------------------------------------

inline const rectangle_t &widget_t::get_region() const
{
    return visible.region;
}

#endif // WIDGET_H
