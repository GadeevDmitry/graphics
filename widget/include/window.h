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
    void header_menu_create_winapi_btn();

protected:
    color_t      color;
    color_menu_t header_menu;

    bool virtual inline on_key_press  (const KEY_TYPE          &key) override;
    bool virtual        on_mouse_press(const MOUSE_BUTTON_TYPE &btn) override;

public:
    explicit window_t(const rectangle_t &region_, const color_t &color_ = Red_theme);
    inline  ~window_t() {}

    bool inline register_subwindow(window_t *window);

    void virtual inline render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline void window_t::window_delete(void *const window_)
{
    window_t *window = *(window_t **) window_;
    delete    window;
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_press  (const KEY_TYPE &key)
{
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::register_subwindow(window_t *window)
{
    return register_subwidget(window);
}

//--------------------------------------------------------------------------------------------------

inline void window_t::render(render_texture_t &wnd) const
{
    wnd.draw_filled_rectangle(visible.region, color, visible);
    subwidgets_render(wnd);
}

#endif // WINDOW_H
