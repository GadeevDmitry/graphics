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
protected:
    void virtual inline move(const vec2d &offset)     override;
    void virtual inline recalc_region()               override;
    void virtual inline render(render_texture_t &wnd) override;

public:
    color_t background;

             inline window_manager_t(void (*delete_window)(void *el),                             const color_t &background_ = color_t::Black);
    explicit inline window_manager_t(void (*delete_window)(void *el), const rectangle_t &region_, const color_t &background_ = color_t::Black);

    bool inline register_window(window_t *window);
    void inline set_region(const rectangle_t &region);
    void inline init();
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
    return register_subwidget(window);
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::init()
{
    recalc_region();
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::move(const vec2d &offset)
{
    visible.region += offset;
    subwidgets_move(offset);
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::recalc_region()
{
    visible.reset();
    subwidgets_recalc_region();
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::render(render_texture_t &wnd)
{
//  wnd.draw_region(visible);
    wnd.draw_rectangle(background, visible);
    subwidgets_render(wnd);
}

#endif // WINDOW_MANAGER_H
