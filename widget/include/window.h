#ifndef WINDOW_H
#define WINDOW_H

#include "menu.h"
#include "canvas.h"
#include "widget_manager.h"

#include "line_tool.h"
#include "ellipse_tool.h"
#include "rectangle_tool.h"
#include "tool_manager.h"

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
    void header_menu_create();
    void header_menu_create_winapi_btn();

protected:
    color_t      color;
    color_menu_t header_menu;

    bool virtual inline on_key_press  (const KEY_TYPE          &key) override;
    bool virtual        on_mouse_press(const MOUSE_BUTTON_TYPE &btn) override;

public:
    explicit window_t(const rectangle_t &region_, const color_t &color_ = window_t::Red_theme);
    inline  ~window_t() {}

    bool inline register_subwindow(window_t *window);

    void virtual inline render(render_texture_t &wnd) override;
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

inline void window_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(color, visible);
    subwidgets_render(wnd);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class main_window_t: public window_t
{
///////////////////////////////////////////////
// TYPE
///////////////////////////////////////////////
private:
    struct tool_button_args
    {
        main_window_t *window;
        tool_t        *tool;
    };

    struct color_button_args
    {
        main_window_t *window;
        color_t       color;
    };

///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
private:
    static bool set_tool_manager_color(widget_t *self, void *args, const MOUSE_BUTTON_TYPE &btn);
    static bool set_tool_manager_tool (widget_t *self, void *args, const MOUSE_BUTTON_TYPE &btn);

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    tool_button_args  * tool_button_args_arr;
    color_button_args *color_button_args_arr;

    void toolbar_create();
    void palette_create();
    void canvas_create ();

    void toolbar_create_tool_btns();
    void palette_create_color_btns();

    void toolbar_create_tool_btn (const button_t::BUTTON_TEXTURE_NAME_TYPE texture, tool_button_args  *args, const vec2d &btn_off);
    void palette_create_color_btn(const button_t::BUTTON_TEXTURE_NAME_TYPE texture, color_button_args *args, const vec2d &btn_off);

protected:
    rectangle_tool_t *rectangle_tool;
    ellipse_tool_t   *ellipse_tool;
    line_tool_t      *line_tool;
    tool_manager_t   tool_manager;

    color_menu_t     toolbar;
    color_menu_t     palette;
    canvas_t         canvas;

public:
    explicit main_window_t(const rectangle_t &region_);
            ~main_window_t();
};

#endif // WINDOW_H
