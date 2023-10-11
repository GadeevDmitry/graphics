#ifndef WIDGET_H
#define WIDGET_H

#include "rendarable.h"

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

    KEY_TYPE_COUNT,
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum MOUSE_BUTTON_TYPE
{
    MOUSE_BUTTON_TYPE_UNKNOWN = -1,

    Left,
    Right,
    Middle,

    MOUSE_BUTTON_TYPE_COUNT,
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class widget_manager_t;

class widget_t: public renderable
{
public:
    struct mouse_context_t
    {
    public:
        vec2d             pos;
        MOUSE_BUTTON_TYPE btn;

                 mouse_context_t();
        explicit mouse_context_t(const vec2d &pos_, const MOUSE_BUTTON_TYPE &btn_);
        inline  ~mouse_context_t() {}

        inline mouse_context_t &operator -=(const vec2d &offset);
        inline mouse_context_t  operator - (const vec2d &offset) const;
    };

    enum WIDGET_STATUS_TYPE
    {
        WIDGET_OPENED,
        WIDGET_CLOSED,
    };

protected:
    typedef bool (widget_t::*on_key_event)   (const KEY_TYPE &key);
    typedef bool (widget_t::*on_mouse_event) (const mouse_context_t &context);

private:
    static mouse_context_t saved_mouse_context;
    static KEY_TYPE        saved_key;

protected:
    WIDGET_STATUS_TYPE status;

public:
    inline          widget_t();
    inline explicit widget_t(const rectangle_t &region_);

    inline WIDGET_STATUS_TYPE get_status() const;

    virtual bool on_key_press  (const KEY_TYPE &key) = 0;
    virtual bool on_key_release(const KEY_TYPE &key) = 0;

    virtual bool on_mouse_press  (const mouse_context_t &context) = 0;
    virtual bool on_mouse_release(const mouse_context_t &context) = 0;
    virtual bool on_mouse_move   (const mouse_context_t &context) = 0;

    virtual inline void recalc_region(const vec2d &offset = vec2d(0, 0)) override {}

    inline static void widget_delete(void *const widget_);

    static const KEY_TYPE        &refresh_key          (const sf::Keyboard::Key &sfml_key);
    static const mouse_context_t &refresh_mouse_pos    (const sf::Vector2i      &sfml_mouse_pos);
    static const mouse_context_t &refresh_mouse_context(const sf::Mouse::Button &sfml_mouse_btn,
                                                        const sf::Vector2i      &sfml_mouse_pos);

    static inline const mouse_context_t &get_mouse_context();
    static inline const KEY_TYPE        &get_key          ();
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

inline widget_t::WIDGET_STATUS_TYPE widget_t::get_status() const
{
    return status;
}

//--------------------------------------------------------------------------------------------------

const widget_t::mouse_context_t &widget_t::get_mouse_context()
{
    return saved_mouse_context;
}

//--------------------------------------------------------------------------------------------------

const KEY_TYPE &widget_t::get_key()
{
    return saved_key;
}

//--------------------------------------------------------------------------------------------------

widget_t::mouse_context_t widget_t::mouse_context_t::operator -(const vec2d &offset) const
{
    return mouse_context_t(pos - offset, btn);
}

//--------------------------------------------------------------------------------------------------

widget_t::mouse_context_t &widget_t::mouse_context_t::operator -=(const vec2d &offset)
{
    return *this = (*this) - offset;
}

#endif // WIDGET_H
