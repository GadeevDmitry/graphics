#ifndef WIDGET_H
#define WIDGET_H

#include "event/eventable.h"
#include "graphic/renderable.h"

//==================================================================================================

class widget_t;

class widget_controller_t
{
// member functions
public:
    virtual inline ~widget_controller_t() {}

// virtual
public:
    virtual bool inline on_key_press    (widget_t *handle, const eventable::key_context_t   &context, const KEY_TYPE          &key);
    virtual bool inline on_key_release  (widget_t *handle, const eventable::key_context_t   &context, const KEY_TYPE          &key);
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn);
    virtual bool        on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn);
    virtual bool inline on_mouse_move   (widget_t *handle, const eventable::mouse_context_t &context, const vec2d             &off);
};

//--------------------------------------------------------------------------------------------------

inline bool widget_controller_t::on_key_press(widget_t *handle, const eventable::key_context_t &context, const KEY_TYPE &key)
{
    (void) handle;
    (void) context;
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool widget_controller_t::on_key_release(widget_t *handle, const eventable::key_context_t &context, const KEY_TYPE &key)
{
    (void) handle;
    (void) context;
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool widget_controller_t::on_mouse_move(widget_t *handle, const eventable::mouse_context_t &context, const vec2d &off)
{
    (void) handle;
    (void) context;
    (void) off;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class widget_t: public eventable, public renderable
{
// types
public:
    enum WIDGET_STATUS_TYPE
    {
        WIDGET_OPENED,
        WIDGET_CLOSED,
        WIDGET_ACTIVATED,
    };

// static
public:
    static widget_t *active;

// member functions
public:
             inline widget_t();
    explicit inline widget_t(const rectangle_t &enclosing);

public:
    void update_ancestral_status(WIDGET_STATUS_TYPE upd_status);

// virtual
public:
    virtual void inline move         (const vec2d &offset);
    virtual void        dump         () const;
    virtual bool inline update_struct();

    virtual void inline recalc_areas () override {}

// member data
public:
    WIDGET_STATUS_TYPE status;
    widget_t          *ancestor;
};

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t():
renderable(),
status    (WIDGET_OPENED),
ancestor  (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t(const rectangle_t &enclosing):
renderable(enclosing),
status    (WIDGET_OPENED),
ancestor  (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline void widget_t::move(const vec2d &offset)
{
    visible.enclosing += offset;
}

//--------------------------------------------------------------------------------------------------

inline bool widget_t::update_struct()
{
    return false;
}

#endif // WIDGET_H
