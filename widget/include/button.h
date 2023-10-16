#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

//==================================================================================================

class button_t: public widget_t
{
public:
    typedef bool (*button_key_click_func)   (button_t *self, void *args, const KEY_TYPE          &key, widget_t *&active);
    typedef void (*button_mouse_click_func) (button_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active);
    typedef void (*button_mouse_move_func)  (button_t *self, void *args, const vec2d             &off, widget_t *&active);

protected:
    button_key_click_func   on_key_press_func;
    button_key_click_func   on_key_release_func;

    button_mouse_click_func on_mouse_press_func;
    button_mouse_click_func on_mouse_release_func;
    button_mouse_move_func  on_mouse_move_func;

    rectangle_t region;
    void        *args;

public:
    inline          button_t();
    inline explicit button_t(const rectangle_t &region_);
    inline         ~button_t() {}

    inline void set_funcs(button_key_click_func   on_key_press_func_  , button_key_click_func   on_key_release_func_,
                          button_mouse_click_func on_mouse_press_func_, button_mouse_click_func on_mouse_release_func_,
                          button_mouse_move_func  on_mouse_move_func_);
    inline void set_args  (void *args_);
    inline void set_region(const rectangle_t &region_);

    virtual inline void move(const vec2d &offset) override;

    virtual bool on_key_press    (const KEY_TYPE          &key) override;
    virtual bool on_key_release  (const KEY_TYPE          &key) override;
    virtual bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_move   (const vec2d             &off) override;

    static bool   activate_by_key_click  (button_t *self, void *args, const KEY_TYPE          &key, widget_t *&active);
    static bool deactivate_by_key_click  (button_t *self, void *args, const KEY_TYPE          &key, widget_t *&active);
    static bool   activate_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active);
    static bool deactivate_by_mouse_click(button_t *self, void *args, const MOUSE_BUTTON_TYPE &btn, widget_t *&active);

    static inline void button_delete(void *const button_);
};

//--------------------------------------------------------------------------------------------------

inline button_t::button_t():
widget_t             (),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

region               (),
args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline button_t::button_t(const rectangle_t &region_):
widget_t             (region_),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

region               (region_),
args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline void button_t::set_funcs(button_key_click_func   on_key_press_func_  , button_key_click_func   on_key_release_func_,
                                button_mouse_click_func on_mouse_press_func_, button_mouse_click_func on_mouse_release_func_,
                                button_mouse_move_func  on_mouse_move_func_)
{
    on_key_press_func     = on_key_press_func_;
    on_key_release_func   = on_key_release_func_;

    on_mouse_press_func   = on_mouse_press_func_;
    on_mouse_release_func = on_mouse_release_func_;
    on_mouse_move_func    = on_mouse_move_func_;
}

//--------------------------------------------------------------------------------------------------

inline void button_t::set_args(void *args_)
{
    args = args_;
}

//--------------------------------------------------------------------------------------------------

inline void button_t::set_region(const rectangle_t &region_)
{
    region = region_;
    visible.region = region_;
}

//--------------------------------------------------------------------------------------------------

inline void button_t::move(const vec2d &offset)
{
    region         += offset;
    visible.region += offset;
}

//--------------------------------------------------------------------------------------------------

inline void button_t::button_delete(void *const button_)
{
    button_t *button = *(button_t **) button_;
    delete    button;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_button_t: public button_t
{
public:
    color_t color;

    inline          color_button_t();
    inline explicit color_button_t(const rectangle_t &region, const color_t &color_);
    inline         ~color_button_t() {}

    virtual inline void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline color_button_t::color_button_t():
color()
{}

//--------------------------------------------------------------------------------------------------

inline color_button_t::color_button_t(const rectangle_t &region_, const color_t &color_):
button_t(region_),
color   (color_)
{}

//--------------------------------------------------------------------------------------------------

inline void color_button_t::render(render_texture_t &wnd) const
{
//  wnd.draw_region(visible);
    wnd.draw_filled_rectangle(region, color, visible);
}

#endif // BUTTON_H
