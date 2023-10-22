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

    bool inline register_window    (window_t *window);
    void inline init_areas         ();
private:
    bool        refresh_after_event();

// virtual
public:
    virtual void inline render          (render_texture_t &wnd)                                        override;
    virtual void inline recalc_areas    ()                                                             override;
    virtual bool        on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool        on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool        on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;

// member data
public:
    color_t background;
};

//--------------------------------------------------------------------------------------------------

inline desktop_t::desktop_t(const color_t &background_):
widget_container_t(),
background        (background_)
{}

//--------------------------------------------------------------------------------------------------

inline desktop_t::desktop_t(const rectangle_t &enclosing, const color_t &background_):
widget_container_t(enclosing),
background        (background_)
{}

//--------------------------------------------------------------------------------------------------

inline bool desktop_t::register_window(window_t *window)
{
    return register_subwidget(window);
}

//--------------------------------------------------------------------------------------------------

inline void desktop_t::init_areas()
{
    recalc_areas();
}

//--------------------------------------------------------------------------------------------------

inline void desktop_t::recalc_areas()
{
    visible.reset_areas();
    subwidgets_recalc_areas();
}

//--------------------------------------------------------------------------------------------------

inline void desktop_t::render(render_texture_t &wnd)
{
//  wnd.draw_region(visible);
    wnd.draw_rectangle(background, visible);
    subwidgets_render(wnd);
}

#endif // DESKTOP_H
