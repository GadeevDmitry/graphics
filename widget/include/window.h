#ifndef WINDOW_H
#define WINDOW_H

#include "menu.h"
#include "widget_manager.h"

//==================================================================================================

class window_t: public widget_manager_t
{
///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
public:
    static const color_t Light_theme;
    static const color_t Dark_theme;
    static const color_t Blue_theme;
    static const color_t Red_theme;

    static inline void window_delete(void *const window_);

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    void create_header_menu();

protected:
    rectangle_t  region;
    color_menu_t header_menu;

public:
    color_t      color;

    explicit window_t(const rectangle_t &region_, const color_t &color_ = Red_theme);
    inline  ~window_t() {}

    inline bool register_sub_window(window_t *window);

    virtual inline void        move      (const vec2d &offset) override;
    virtual inline rectangle_t get_region() const              override;

    virtual inline bool on_key_press    (const KEY_TYPE          &key) override;
    virtual inline bool on_key_release  (const KEY_TYPE          &key) override;
    virtual        bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    virtual inline bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    virtual inline bool on_mouse_move   (const vec2d             &off) override;

    virtual inline void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline void window_t::move(const vec2d &offset)
{
    region         += offset;
    visible.region += offset;

    widgets_move(offset);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::register_sub_window(window_t *window)
{
    return register_widget(window);
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t window_t::get_region() const
{
    return region;
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_press  (const KEY_TYPE &key) { (void) key; return false; }
inline bool window_t::on_key_release(const KEY_TYPE &key) { (void) key; return false; }

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn) { return on_widgets_mouse_release(btn); }
bool window_t::on_mouse_move   (const vec2d             &off) { return on_widgets_mouse_move   (off); }

//--------------------------------------------------------------------------------------------------

inline void window_t::render(render_texture_t &wnd) const
{
    wnd.draw_filled_rectangle(region, color, visible);
    widgets_render(wnd);
}

//--------------------------------------------------------------------------------------------------

inline void window_t::window_delete(void *const window_)
{
    window_t *window = *(window_t **) window_;
    delete    window;
}

#endif // WINDOW_H
