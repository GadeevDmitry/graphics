#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "window.h"
#include "widget_manager.h"

//==================================================================================================

class window_manager_t: public widget_manager_t
{
public:
    inline          window_manager_t();
    inline explicit window_manager_t(const rectangle_t &region_, widget_t *parent_);

    inline bool register_window(window_t *window);

    virtual inline bool on_key_press  (const KEY_TYPE &key) override;
    virtual inline bool on_key_release(const KEY_TYPE &key) override;

    virtual inline bool on_mouse_press  (const mouse_context_t &context) override;
    virtual inline bool on_mouse_release(const mouse_context_t &context) override;

    virtual inline void render(render_texture_t &render_texture) const override;
};

//--------------------------------------------------------------------------------------------------

inline window_manager_t::window_manager_t():
widget_manager_t()
{}

//--------------------------------------------------------------------------------------------------

inline window_manager_t::window_manager_t(const rectangle_t &region_, widget_t *parent_):
widget_manager_t(region_, parent_)
{}

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

inline void window_manager_t::render(render_texture_t &render_texture) const
{
    return widgets_render(render_texture);
}

#endif // WINDOW_MANAGER_H
