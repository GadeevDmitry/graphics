#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include "data_structs/include/log.h"

//==================================================================================================

class button_t: public widget_t
{
// member functions
public:
    explicit inline  button_t(widget_controller_t &controller);
    explicit inline  button_t(widget_controller_t &controller, const rectangle_t &enclosing);

// virtual
public:
    virtual bool inline on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;

// member data
protected:
    widget_controller_t &controller;
};

//--------------------------------------------------------------------------------------------------

inline button_t::button_t(widget_controller_t &controller_):
widget_t  (),
controller(controller_)
{}

//--------------------------------------------------------------------------------------------------

inline button_t::button_t(widget_controller_t &controller_, const rectangle_t &enclosing):
widget_t  (enclosing),
controller(controller_)
{}

//--------------------------------------------------------------------------------------------------

inline bool button_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == nullptr, false);
    return controller.on_key_press(this, context, key);
}

//--------------------------------------------------------------------------------------------------

inline bool button_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == this, false);
    return controller.on_key_release(this, context, key);
}

//--------------------------------------------------------------------------------------------------

inline bool button_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == this, false);
    return controller.on_mouse_release(this, context, btn);
}

//--------------------------------------------------------------------------------------------------

inline bool button_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    LOG_VERIFY(active == this, false);
    return controller.on_mouse_move(this, context, off);
}

#endif // BUTTON_H
