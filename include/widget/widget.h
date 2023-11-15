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

    void update_ancestral_status(WIDGET_STATUS_TYPE upd_status);

// virtual
public:
    virtual void inline move           (const vec2d &offset);
    virtual void        dump           () const;
    virtual void inline graphic_dump   (render_texture_t &wnd) const;
    virtual bool inline update_struct  ();
    virtual void inline recalc_regions () override {}
protected:
    virtual void inline dump_class_name() const;

// member data
public:
    WIDGET_STATUS_TYPE status;
    widget_t          *ancestor;
};

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t():
eventable (),
renderable(),
status    (WIDGET_OPENED),
ancestor  (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline widget_t::widget_t(const rectangle_t &enclosing_):
eventable (),
renderable(enclosing_),
status    (WIDGET_OPENED),
ancestor  (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline void widget_t::move(const vec2d &offset)
{
    enclosing += offset;
}

//--------------------------------------------------------------------------------------------------

inline void widget_t::graphic_dump(render_texture_t &wnd) const
{
    wnd.draw_region(own_visible);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_t::update_struct()
{
    return false;
}

//--------------------------------------------------------------------------------------------------

inline void widget_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("widget_t", "");
}

#endif // WIDGET_H
