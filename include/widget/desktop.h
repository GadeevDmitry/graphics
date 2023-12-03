#ifndef DESKTOP_H
#define DESKTOP_H

#include "window.h"
#include "widget_container.h"

//==================================================================================================

class desktop_t: public widget_container_t
{
// member functions
public:
    explicit inline desktop_t(                              const color_t &background = color_t::Black);
    explicit inline desktop_t(const rectangle_t &enclosing, const color_t &background = color_t::Black);

    bool inline register_window(window_t *window);
    void        render_initial (render_texture_t &wnd);
private:
    bool        refresh_after_event();

// virtual
public:
    virtual void        render          (render_texture_t &wnd)                                        override;
    virtual void inline recalc_regions  ()                                                             override;
    virtual bool        on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool        on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool        on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;
protected:
    virtual void inline dump_class_name () const override;

// member data
public:
    color_t background;
};

//--------------------------------------------------------------------------------------------------

inline desktop_t::desktop_t(const color_t &background_):
widget_container_t(true),
background        (background_)
{}

//--------------------------------------------------------------------------------------------------

inline desktop_t::desktop_t(const rectangle_t &enclosing_, const color_t &background_):
widget_container_t(enclosing_, true),
background        (background_)
{}

//--------------------------------------------------------------------------------------------------

inline bool desktop_t::register_window(window_t *window)
{
    return register_subwidget(widget_proxy_t(window));
}

//--------------------------------------------------------------------------------------------------

inline void desktop_t::recalc_regions()
{
    reset_regions();
    subwidgets_recalc_regions();
}

//--------------------------------------------------------------------------------------------------

inline void desktop_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("desktop_t", "");
}

#endif // DESKTOP_H
