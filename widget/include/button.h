#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

//==================================================================================================

class button_t: public widget_t
{
protected:
    typedef bool (*button_key_func)   (void *, const KEY_TYPE &key);
    typedef bool (*button_mouse_func) (void *, const mouse_context_t &context);

    button_key_func on_key_press_func;
    button_key_func on_key_release_func;

    button_mouse_func on_mouse_press_func;
    button_mouse_func on_mouse_release_func;
    button_mouse_func on_mouse_move_func;

    MOUSE_BUTTON_TYPE saved_mouse_btn;
    KEY_TYPE          saved_key;

    void        *args;
    rectangle_t region;

public:
    inline          button_t();
    inline explicit button_t(const rectangle_t &region_);
    inline         ~button_t() {}

    inline void set_funcs(button_key_func   on_key_press_func_  , button_key_func   on_key_release_func_,
                          button_mouse_func on_mouse_press_func_, button_mouse_func on_mouse_release_func_,
                          button_mouse_func on_mouse_move_func_);

    inline void set_args  (void *args_);
    inline void set_region(const rectangle_t &region_);

    bool on_key_press  (const KEY_TYPE &key) override;
    bool on_key_release(const KEY_TYPE &key) override;

    bool on_mouse_press  (const mouse_context_t &context) override;
    bool on_mouse_release(const mouse_context_t &context) override;
    bool on_mouse_move   (const mouse_context_t &context) override;

    inline static void button_delete(void *const button_);
};

//--------------------------------------------------------------------------------------------------

inline button_t::button_t():
widget_t             (),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

saved_mouse_btn      (MOUSE_BUTTON_TYPE_UNKNOWN),
saved_key            (KEY_TYPE_UNKNOWN),

args                 (nullptr),
region               ()
{}

//--------------------------------------------------------------------------------------------------

inline button_t::button_t(const rectangle_t &region_):
widget_t             (region_),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

saved_mouse_btn      (MOUSE_BUTTON_TYPE_UNKNOWN),
saved_key            (KEY_TYPE_UNKNOWN),

args                 (nullptr),
region               (region_)
{}

//--------------------------------------------------------------------------------------------------

inline void button_t::set_funcs(button_key_func   on_key_press_func_  , button_key_func   on_key_release_func_,
                                button_mouse_func on_mouse_press_func_, button_mouse_func on_mouse_release_func_,
                                button_mouse_func on_mouse_move_func_)
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
    visible.set_region(region_);
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

    virtual inline void render(render_texture_t &wnd, const vec2d &offset = vec2d(0, 0)) const override;
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

inline void color_button_t::render(render_texture_t &wnd, const vec2d &offset) const
{
    wnd.draw_filled_rectangle(region + offset, color, visible);
}

#endif // BUTTON_H
