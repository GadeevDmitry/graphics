#ifndef EXTERNAL_CANVAS_BUTTON_H
#define EXTERNAL_CANVAS_BUTTON_H

#include "label_button.h"
#include "widget/window/canvas_window.h"

//==================================================================================================

class external_canvas_button_controller_t: public widget_controller_t
{
// member functions
public:
    inline external_canvas_button_controller_t() {}

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
};

//--------------------------------------------------------------------------------------------------

inline bool external_canvas_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class external_canvas_button_t: public label_button_t
{
// member functions
public:
    explicit inline external_canvas_button_t(external_canvas_button_controller_t &controller,                               const char *canvas_name, canvas_window_t *canvas_wnd = nullptr);
    explicit inline external_canvas_button_t(external_canvas_button_controller_t &controller, const rectangle_t &enclosing, const char *canvas_name, canvas_window_t *canvas_wnd = nullptr);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    canvas_window_t *canvas_window;
};

//--------------------------------------------------------------------------------------------------

inline external_canvas_button_t::external_canvas_button_t(external_canvas_button_controller_t &controller_, const char *canvas_name, canvas_window_t *canvas_wnd):
label_button_t(controller_, canvas_name, 20),
canvas_window (canvas_wnd)
{}

//--------------------------------------------------------------------------------------------------

inline external_canvas_button_t::external_canvas_button_t(external_canvas_button_controller_t &controller_, const rectangle_t &enclosing_, const char *canvas_name, canvas_window_t *canvas_wnd):
label_button_t(controller_, enclosing, canvas_name, 20),
canvas_window (canvas_wnd)
{}

//--------------------------------------------------------------------------------------------------

inline void external_canvas_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_canvas_button_t", "");
}

#endif // EXTERNAL_CANVAS_BUTTON_H
