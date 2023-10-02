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

    KEY_TYPE_COUNT
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum MOUSE_BUTTON_TYPE
{
    MOUSE_BUTTON_TYPE_UNKNOWN = -1,

    Left,
    Right,
    Middle,

    MOUSE_BUTTON_TYPE_COUNT
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class widget_t: public renderable
{
public:
    enum WIDGET_STATUS_TYPE
    {
        WIDGET_OPENED,
        WIDGET_CLOSED,
    };

    static KEY_TYPE          convert_key      (const sf::Keyboard::Key sfml_key);
    static MOUSE_BUTTON_TYPE convert_mouse_btn(const sf::Mouse::Button sfml_mouse_btn);

    inline widget_t();
    inline WIDGET_STATUS_TYPE get_status();

    virtual bool on_key_press  (const KEY_TYPE key) = 0;
    virtual bool on_key_release(const KEY_TYPE key) = 0;

    virtual bool on_mouse_press  (const vec2d &pos, const MOUSE_BUTTON_TYPE btn) = 0;
    virtual bool on_mouse_release(const vec2d &pos, const MOUSE_BUTTON_TYPE btn) = 0;

protected:
    typedef bool (widget_t::*  key_event) (const KEY_TYPE key);
    typedef bool (widget_t::*mouse_event) (const vec2d &pos, const MOUSE_BUTTON_TYPE btn);

    inline static void widget_delete(void *const widget_);

private:
    WIDGET_STATUS_TYPE status;
};

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t():
status(WIDGET_OPENED)
{}

//--------------------------------------------------------------------------------------------------

inline widget_t::WIDGET_STATUS_TYPE widget_t::get_status()
{
    return status;
}

//--------------------------------------------------------------------------------------------------

inline void widget_t::widget_delete(void *const widget_)
{
    widget_t *widget = *(widget_t **) widget_;
    delete    widget;
}

#endif // WIDGET_H
