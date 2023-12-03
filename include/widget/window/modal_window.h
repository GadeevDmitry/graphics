#ifndef MODAL_WINDOW_H
#define MODAL_WINDOW_H

#include "widget/window.h"

//==================================================================================================

class modal_window_t: public window_t
{
// member functions
public:
    explicit modal_window_t(event_manager_t &event_manager,                               const color_t &color, const char *wnd_name);
    explicit modal_window_t(event_manager_t &event_manager, const rectangle_t &enclosing, const color_t &color, const char *wnd_name);
            ~modal_window_t();

// virtual
public:
    virtual bool on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
protected:
    event_manager_t &event_manager;
};

//--------------------------------------------------------------------------------------------------

inline void modal_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("modal_window_t", "");
}

#endif // MODAL_WINDOW_H
