#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "widget_manager.h"

//==================================================================================================

class window_t;

class menu_t: public widget_manager_t
{
///////////////////////////////////////////////
// FRIENDS
///////////////////////////////////////////////
friend window_t;

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    widget_key_click_func   on_key_press_func;
    widget_key_click_func   on_key_release_func;

    widget_mouse_click_func on_mouse_press_func;
    widget_mouse_click_func on_mouse_release_func;
    widget_mouse_move_func  on_mouse_move_func;

    void *args;

    bool virtual on_key_press    (const KEY_TYPE          &key) override;
    bool virtual on_key_release  (const KEY_TYPE          &key) override;
    bool virtual on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    bool virtual on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    bool virtual on_mouse_move   (const vec2d             &off) override;

public:
    explicit inline  menu_t(void (*delete_button)(void *el));
    explicit inline  menu_t(void (*delete_button)(void *el), const rectangle_t &region_);
             inline ~menu_t() {}

    void inline set_funcs (widget_key_click_func   on_key_press_func_,   widget_key_click_func   on_key_release_func_,
                           widget_mouse_click_func on_mouse_press_func_, widget_mouse_click_func on_mouse_release_func_,
                           widget_mouse_move_func  on_mouse_move_func_);
    void inline set_args  (void *args_);
    void inline set_region(const rectangle_t &region);

    bool inline register_button(button_t *button);
};

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(void (*delete_button)(void *el)):
widget_manager_t     (delete_button),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(void (*delete_button)(void *el), const rectangle_t &region_):
widget_manager_t     (delete_button, region_),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline void menu_t::set_funcs(widget_key_click_func   on_key_press_func_,   widget_key_click_func   on_key_release_func_,
                              widget_mouse_click_func on_mouse_press_func_, widget_mouse_click_func on_mouse_release_func_,
                              widget_mouse_move_func on_mouse_move_func_)
{
    on_key_press_func     = on_key_press_func_;
    on_key_release_func   = on_key_release_func_;

    on_mouse_press_func   = on_mouse_press_func_;
    on_mouse_release_func = on_mouse_release_func_;
    on_mouse_move_func    = on_mouse_move_func_;
}

//--------------------------------------------------------------------------------------------------

inline void menu_t::set_args(void *args_)
{
    args = args_;
}

//--------------------------------------------------------------------------------------------------

inline void menu_t::set_region(const rectangle_t &region)
{
    visible.region = region;
}

//--------------------------------------------------------------------------------------------------

inline bool menu_t::register_button(button_t *button)
{
    return register_subwidget(button);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_menu_t: public menu_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    color_t color;

    explicit inline  color_menu_t(void (*delete_button)(void *el));
    explicit inline  color_menu_t(void (*delete_button)(void *el), const rectangle_t &region_, const color_t &color_);
             inline ~color_menu_t() {}

    void virtual inline render(render_texture_t &wnd) override;
};

//--------------------------------------------------------------------------------------------------

inline color_menu_t::color_menu_t(void (*delete_button)(void *el)):
menu_t(delete_button),
color ()
{}

//--------------------------------------------------------------------------------------------------

inline color_menu_t::color_menu_t(void (*delete_button)(void *el), const rectangle_t &region_, const color_t &color_):
menu_t(delete_button, region_),
color (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void color_menu_t::render(render_texture_t &wnd)
{
//  wnd.draw_region(visible);
    wnd.draw_filled_rectangle(visible.region, color, visible);
    subwidgets_render(wnd);
}

#endif // MENU_H
