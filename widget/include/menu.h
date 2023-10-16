#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "widget_manager.h"

//==================================================================================================

class menu_t: public widget_manager_t
{
///////////////////////////////////////////////
// TYPES
///////////////////////////////////////////////
public:
    typedef bool (*menu_key_click_func)   (menu_t *self, void *args, const KEY_TYPE          &key, widget_t *&active);
    typedef bool (*menu_mouse_click_func) (menu_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active);
    typedef void (*menu_mouse_move_func)  (menu_t *self, void *args, const vec2d             &off, widget_t *&active);

///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
public:
    static bool   activate_by_key_click  (menu_t *self, void *args, const KEY_TYPE          &key, widget_t *&active);
    static bool deactivate_by_key_click  (menu_t *self, void *args, const KEY_TYPE          &key, widget_t *&active);
    static bool   activate_by_mouse_click(menu_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active);
    static bool deactivate_by_mouse_click(menu_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active);

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    menu_key_click_func   on_key_press_func;
    menu_key_click_func   on_key_release_func;

    menu_mouse_click_func on_mouse_press_func;
    menu_mouse_click_func on_mouse_release_func;
    menu_mouse_move_func  on_mouse_move_func;

    rectangle_t region;
    void        *args;

public:
    inline          menu_t(void (*delete_button)(void *el));
    inline explicit menu_t(void (*delete_button)(void *el), const rectangle_t &region_);
    inline         ~menu_t() {}

    inline void set_funcs (menu_key_click_func   on_key_press_func_,   menu_key_click_func   on_key_release_func_,
                           menu_mouse_click_func on_mouse_press_func_, menu_mouse_click_func on_mouse_release_func_,
                           menu_mouse_move_func  on_mouse_move_func_);
    inline void set_args  (void *args_);
    inline void set_region(const rectangle_t &region_);

    inline bool register_button(button_t *button);

    virtual inline void        move      (const vec2d &offset) override;
    virtual inline rectangle_t get_region() const              override;

    virtual bool on_key_press    (const KEY_TYPE          &key) override;
    virtual bool on_key_release  (const KEY_TYPE          &key) override;
    virtual bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_move   (const vec2d             &off) override;
};

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(void (*delete_button)(void *el)):
widget_manager_t     (delete_button),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

region               (),
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

region               (region_),
args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline void menu_t::set_funcs(menu_key_click_func   on_key_press_func_,   menu_key_click_func   on_key_release_func_,
                              menu_mouse_click_func on_mouse_press_func_, menu_mouse_click_func on_mouse_release_func_,
                              menu_mouse_move_func on_mouse_move_func_)
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

inline void menu_t::set_region(const rectangle_t &region_)
{
    region = region_;
    visible.region = region_;
}

//--------------------------------------------------------------------------------------------------

inline bool menu_t::register_button(button_t *button)
{
    return register_widget(button);
}

//--------------------------------------------------------------------------------------------------

inline void menu_t::move(const vec2d &offset)
{
    region         += offset;
    visible.region += offset;
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t menu_t::get_region() const
{
    return region;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_menu_t: public menu_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    color_t color;

    inline          color_menu_t(void (*delete_button)(void *el));
    inline explicit color_menu_t(void (*delete_button)(void *el), const rectangle_t &region_, const color_t &color_);
    inline         ~color_menu_t() {}

    virtual inline void render(render_texture_t &wnd) const override;
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

inline void color_menu_t::render(render_texture_t &wnd) const
{
//  wnd.draw_region(visible);
    wnd.draw_filled_rectangle(region, color, visible);
    widgets_render(wnd);
}

#endif // MENU_H
