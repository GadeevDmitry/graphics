#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "window.h"
#include "widget_manager.h"

//==================================================================================================

class window_manager_t: public widget_manager_t
{
public:
    inline          window_manager_t(void (*delete_window)(void *el));
    inline explicit window_manager_t(void (*delete_window)(void *el), const rectangle_t &region_);

    inline void set_region     (const rectangle_t &region);
    inline bool register_window(window_t *window);
};

//--------------------------------------------------------------------------------------------------

inline window_manager_t::window_manager_t(void (*delete_window) (void *el)):
widget_manager_t(delete_window)
{}

//--------------------------------------------------------------------------------------------------

inline window_manager_t::window_manager_t(void (*delete_window) (void *el), const rectangle_t &region_):
widget_manager_t(delete_window, region_)
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

#endif // WINDOW_MANAGER_H
