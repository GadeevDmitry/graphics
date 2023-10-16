#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "window.h"
#include "widget_manager.h"

//==================================================================================================

class window_manager_t: public widget_manager_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    color_t background;

    inline          window_manager_t(void (*delete_window)(void *el),                             const color_t &background_ = color_t::Black);
    inline explicit window_manager_t(void (*delete_window)(void *el), const rectangle_t &region_, const color_t &background_ = color_t::Black);

    inline void set_region     (const rectangle_t &region);
    inline bool register_window(window_t *window);

    virtual inline rectangle_t get_region() const override;

    virtual inline void recalc_region()                     override;
    virtual inline void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline window_manager_t::window_manager_t(void (*delete_window) (void *el), const color_t &background_):
widget_manager_t(delete_window),
background      (background_)
{}

//--------------------------------------------------------------------------------------------------

inline window_manager_t::window_manager_t(void (*delete_window) (void *el), const rectangle_t &region_, const color_t &background_):
widget_manager_t(delete_window, region_),
background      (background_)
{}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::set_region(const rectangle_t &region)
{
    visible.region = region;
}

//--------------------------------------------------------------------------------------------------

inline bool window_manager_t::register_window(window_t *window)
{
    return register_widget(window);
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t window_manager_t::get_region() const
{
    return visible.region;
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::recalc_region()
{
    visible.reset();
    widgets_recalc_region();
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::render(render_texture_t &wnd) const
{
//  wnd.draw_region(visible);
    wnd.draw_filled_rectangle(visible.region, background, visible);
    widgets_render(wnd);
}

#endif // WINDOW_MANAGER_H
