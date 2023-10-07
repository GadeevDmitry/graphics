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

class widget_t: public renderable
{
public:
    struct mouse_context_t
    {
    public:
        vec2d             pos;
        MOUSE_BUTTON_TYPE btn;

        explicit mouse_context_t(const sf::Mouse::Button &sfml_mouse_btn_,
                                 const sf::Vector2i      &sfml_mouse_pos_);

        inline ~mouse_context_t() {}
    };

protected:
    enum WIDGET_STATUS_TYPE
    {
        WIDGET_OPENED,
        WIDGET_CLOSED,
    }
    status;

public:
    inline widget_t();

    inline WIDGET_STATUS_TYPE get_status() const;

    static KEY_TYPE key_t(const sf::Keyboard::Key &sfml_key);

    virtual bool on_key_press  (const KEY_TYPE &key) = 0;
    virtual bool on_key_release(const KEY_TYPE &key) = 0;

    virtual bool on_mouse_press  (const mouse_context_t &context) = 0;
    virtual bool on_mouse_release(const mouse_context_t &context) = 0;

protected:

    typedef bool (widget_t::*on_key_event)   (const KEY_TYPE &key);
    typedef bool (widget_t::*on_mouse_event) (const mouse_context_t &context);

    inline static void widget_delete(void *const widget_);
};

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t():
status(WIDGET_OPENED)
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

#endif // WIDGET_H
