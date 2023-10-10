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

    inline bool set_region     (const rectangle_t &region);
    inline bool register_window(window_t *window);

    virtual inline bool on_key_press  (const KEY_TYPE &key) override;
    virtual inline bool on_key_release(const KEY_TYPE &key) override;

    virtual inline bool on_mouse_press  (const mouse_context_t &context) override;
    virtual inline bool on_mouse_release(const mouse_context_t &context) override;

    virtual inline void render(render_texture_t &render_texture, const vec2d &offset = vec2d(0, 0)) const override;
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

inline bool window_manager_t::set_region(const rectangle_t &region)
{
    return visible.set_region(region);
}

//--------------------------------------------------------------------------------------------------

inline bool window_manager_t::register_window(window_t *window)
{
    return register_widget(window);
}

//--------------------------------------------------------------------------------------------------

inline bool window_manager_t::on_key_press(const KEY_TYPE &key)
{
    return on_widgets_key_press(key);
}

//--------------------------------------------------------------------------------------------------

inline bool window_manager_t::on_key_release(const KEY_TYPE &key)
{
    return on_widgets_key_release(key);
}

//--------------------------------------------------------------------------------------------------

inline bool window_manager_t::on_mouse_press(const mouse_context_t &mouse)
{
    return on_mouse_press(mouse);
}

//--------------------------------------------------------------------------------------------------

inline bool window_manager_t::on_mouse_release(const mouse_context_t &mouse)
{
    return on_mouse_release(mouse);
}

//--------------------------------------------------------------------------------------------------

inline void window_manager_t::render(render_texture_t &render_texture, const vec2d &offset) const
{
    return widgets_render(render_texture, offset);
}

#endif // WINDOW_MANAGER_H
