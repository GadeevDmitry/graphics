#ifndef WINDOW_H
#define WINDOW_H

#include "menu.h"
#include "widget_manager.h"

//==================================================================================================

class window_t: public widget_manager_t
{
protected:
    rectangle_t  region;
    color_menu_t header_menu;

public:
    explicit window_t(const rectangle_t &region_);
    inline  ~window_t() {}

    virtual inline void move(const vec2d &offset) override;

    virtual inline bool on_key_press    (const KEY_TYPE          &key) override;
    virtual inline bool on_key_release  (const KEY_TYPE          &key) override;
    virtual        bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    virtual inline bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    virtual inline bool on_mouse_move   (const vec2d             &off) override;

    static inline void window_delete(void *const window_);
};

//--------------------------------------------------------------------------------------------------

inline void window_t::move(const vec2d &offset)
{
    region         += offset;
    visible.region += offset;

    widgets_move(offset);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_press  (const KEY_TYPE &key) { (void) key; return false; }
inline bool window_t::on_key_release(const KEY_TYPE &key) { (void) key; return false; }

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn) { return on_widgets_mouse_release(btn); }
bool window_t::on_mouse_move   (const vec2d             &off) { return on_widgets_mouse_move   (off); }

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

    inline explicit color_window_t(const rectangle_t &region_, const color_t &color_ = color_t::White);
    inline         ~color_window_t() {}

    virtual inline void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t(const rectangle_t &region_, const color_t &color_):
window_t(region_),
color   (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void color_window_t::render(render_texture_t &wnd) const
{
    wnd.draw_region(visible);
    widgets_render(wnd);
}

#endif // WINDOW_H
