#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "widget_manager.h"

//==================================================================================================

class menu_t: public widget_manager_t
{
protected:
    typedef bool (*menu_mouse_func) (void *, const mouse_context_t &context);

    menu_mouse_func on_mouse_move_func;
    MOUSE_BUTTON_TYPE  saved_mouse_btn;

    void        *args;
    rectangle_t region;

public:
    inline          menu_t(void (*delete_button)(void *el));
    inline explicit menu_t(void (*delete_button)(void *el), const rectangle_t &region_, menu_mouse_func on_mouse_move_func_);
    inline         ~menu_t() {}

    inline void set_func  (menu_mouse_func on_mouse_move_func_);
    inline void set_args  (void *args_);
    inline bool set_region(const rectangle_t &region_);

    inline bool register_button(button_t *button);

    virtual inline bool on_key_press  (const KEY_TYPE &key) override;
    virtual inline bool on_key_release(const KEY_TYPE &key) override;

    virtual bool on_mouse_press  (const mouse_context_t &context) override;
    virtual bool on_mouse_release(const mouse_context_t &context) override;
    virtual bool on_mouse_move   (const mouse_context_t &context) override;
};

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(void (*delete_button)(void *el)):
widget_manager_t  (delete_button),
on_mouse_move_func(nullptr),
saved_mouse_btn   (MOUSE_BUTTON_TYPE_UNKNOWN),
args              (nullptr),
region            ()
{}

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(void (*delete_button)(void *el), const rectangle_t &region_, menu_mouse_func on_mouse_move_func_):
widget_manager_t  (delete_button, region_),
on_mouse_move_func(on_mouse_move_func_),
saved_mouse_btn   (MOUSE_BUTTON_TYPE_UNKNOWN),
args              (nullptr),
region            (region_)
{}

//--------------------------------------------------------------------------------------------------

inline void menu_t::set_func(menu_mouse_func on_mouse_move_func_)
{
    on_mouse_move_func = on_mouse_move_func_;
}

//--------------------------------------------------------------------------------------------------

inline void menu_t::set_args(void *args_)
{
    args = args_;
}

//--------------------------------------------------------------------------------------------------

inline bool menu_t::set_region(const rectangle_t &region_)
{
    region = region_;
    return visible.set_region(region_);
}

//--------------------------------------------------------------------------------------------------

inline bool menu_t::register_button(button_t *button)
{
    return register_widget(button);
}

//--------------------------------------------------------------------------------------------------

inline bool menu_t::on_key_press(const KEY_TYPE &key)
{
    return on_widgets_key_press(key);
}

//--------------------------------------------------------------------------------------------------

inline bool menu_t::on_key_release(const KEY_TYPE &key)
{
    return on_widgets_key_release(key);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_menu_t: public menu_t
{
public:
    color_t color;

    inline          color_menu_t(void (*delete_button)(void *el));
    inline explicit color_menu_t(void (*delete_button)(void *el), const rectangle_t &region_,
                                 menu_mouse_func on_mouse_move_func_, const color_t &color_);
    inline         ~color_menu_t() {}

    virtual inline void render(render_texture_t &wnd, const vec2d &offset = vec2d(0, 0)) const override;
};

//--------------------------------------------------------------------------------------------------

inline color_menu_t::color_menu_t(void (*delete_button)(void *el)):
menu_t(delete_button),
color ()
{}

//--------------------------------------------------------------------------------------------------

inline color_menu_t::color_menu_t(void (*delete_button)(void *el), const rectangle_t &region_,
                                  menu_mouse_func on_mouse_move_func_, const color_t &color_):
menu_t(delete_button, region_, on_mouse_move_func_),
color (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void color_menu_t::render(render_texture_t &wnd, const vec2d &offset) const
{
    wnd.draw_filled_rectangle(region + offset, color, visible);
    widgets_render(wnd, offset + region.ld_corner);
}

#endif // MENU_H
