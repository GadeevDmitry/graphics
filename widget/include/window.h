#ifndef WINDOW_H
#define WINDOW_H

#include "widget_manager.h"

//==================================================================================================

class window_t: public widget_manager_t
{
protected:
    rectangle_t region;

public:
    inline          window_t();
    inline explicit window_t(const rectangle_t &region_);

    inline bool set_region(const rectangle_t &reginon_);

    virtual inline bool on_key_press  (const KEY_TYPE &key) override;
    virtual inline bool on_key_release(const KEY_TYPE &key) override;

    virtual inline bool on_mouse_press  (const mouse_context_t &context) override;
    virtual inline bool on_mouse_release(const mouse_context_t &context) override;
    virtual inline bool on_mouse_move   (const mouse_context_t &context) override;

    inline static void window_delete(void *const window_);
};

//--------------------------------------------------------------------------------------------------

inline window_t::window_t():
widget_manager_t(nullptr),
region()
{}

//--------------------------------------------------------------------------------------------------

inline window_t::window_t(const rectangle_t &region_):
widget_manager_t(nullptr, region_),
region          (region_)
{}

//--------------------------------------------------------------------------------------------------

inline bool window_t::set_region(const rectangle_t &region_)
{
    region = region_;
    return visible.set_region(region_);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_press  (const KEY_TYPE &key) { return false; }
inline bool window_t::on_key_release(const KEY_TYPE &key) { return false; }

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_mouse_press  (const mouse_context_t &context) { return false; }
inline bool window_t::on_mouse_release(const mouse_context_t &context) { return false; }
inline bool window_t::on_mouse_move   (const mouse_context_t &context) { return false; }

//--------------------------------------------------------------------------------------------------

inline void window_t::window_delete(void *const window_)
{
    window_t *window = *(window_t **) window_;
    delete    window;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_window_t: public window_t
{
public:
    color_t color;

    inline          color_window_t();
    inline explicit color_window_t(const rectangle_t &region_, const color_t &color_);
    inline         ~color_window_t() {}

    virtual inline void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t():
color()
{}

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t(const rectangle_t &region_, const color_t &color_):
window_t(region_),
color   (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void color_window_t::render(render_texture_t &wnd) const
{
    wnd.draw_filled_rectangle(region, color);
    widgets_render(wnd);
}

#endif // WINDOW_H
