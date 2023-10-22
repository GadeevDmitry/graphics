#ifndef BUTTON_H
#define BUTTON_H

#include "log.h"
#include "widget.h"

//==================================================================================================

class button_t: public widget_t
{
///////////////////////////////////////////////
// TYPES
///////////////////////////////////////////////
public:
    enum BUTTON_TEXTURE_NAME_TYPE
    {
        BUTTON_TEXTURE_NAME_UNKNOWN = -1,

        RED_WINAPI,
        BLUE_WINAPI,
        GREEN_WINAPI,

        LINE_ON_TOOL,
        LINE_OFF_TOOL,
        PENCIL_ON_TOOL,
        PENCIL_OFF_TOOL,
        RUBBER_ON_TOOL,
        RUBBER_OFF_TOOL,
        ELLIPSE_ON_TOOL,
        ELLIPSE_OFF_TOOL,
        RECTANGLE_ON_TOOL,
        RECTANGLE_OFF_TOOL,

        WHITE_ON_COLOR,
        WHITE_OFF_COLOR,
        BLUE_ON_COLOR,
        BLUE_OFF_COLOR,
        RED_ON_COLOR,
        RED_OFF_COLOR,
        ORANGE_ON_COLOR,
        ORANGE_OFF_COLOR,
        GREEN_ON_COLOR,
        GREEN_OFF_COLOR,
        BLACK_ON_COLOR,
        BLACK_OFF_COLOR,

        BUTTON_TEXTURE_NAME_COUNT,
    };

///////////////////////////////////////////////
// STATIC
///////////////////////////////////////////////
private:
    static const char *BUTTON_TEXTURES_FILENAMES[];

protected:
    static texture_t BUTTON_TEXTURES[];

public:
    static void        load_textures();
    static void inline button_delete(void *const button_);

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
             inline  button_t();
    explicit inline  button_t(const rectangle_t &region_);
             inline ~button_t() {}

    void inline set_funcs(widget_key_click_func   on_key_press_func_  , widget_key_click_func   on_key_release_func_,
                          widget_mouse_click_func on_mouse_press_func_, widget_mouse_click_func on_mouse_release_func_,
                          widget_mouse_move_func  on_mouse_move_func_);
    void inline set_args  (void *args_);
    void inline set_region(const rectangle_t &region);
};

//--------------------------------------------------------------------------------------------------

inline button_t::button_t():
widget_t             (),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline button_t::button_t(const rectangle_t &region):
widget_t             (region),

on_key_press_func    (nullptr),
on_key_release_func  (nullptr),
on_mouse_press_func  (nullptr),
on_mouse_release_func(nullptr),
on_mouse_move_func   (nullptr),

args                 (nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline void button_t::set_funcs(widget_key_click_func   on_key_press_func_  , widget_key_click_func   on_key_release_func_,
                                widget_mouse_click_func on_mouse_press_func_, widget_mouse_click_func on_mouse_release_func_,
                                widget_mouse_move_func  on_mouse_move_func_)
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

inline void button_t::set_region(const rectangle_t &region)
{
    visible.region = region;
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
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    color_t color;

             inline  color_button_t();
    explicit inline  color_button_t(const rectangle_t &region, const color_t &color_);
             inline ~color_button_t() {}

    void virtual inline render(render_texture_t &wnd) override;
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

inline void color_button_t::render(render_texture_t &wnd)
{
//  wnd.draw_region(visible);
    wnd.draw_filled_rectangle(visible.region, color, visible);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class texture_button_t: public button_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
public:
    const texture_t &texture;

    explicit inline  texture_button_t(const BUTTON_TEXTURE_NAME_TYPE name);
    explicit inline  texture_button_t(const BUTTON_TEXTURE_NAME_TYPE name, const rectangle_t &region_);
             inline ~texture_button_t() {}

    void virtual inline render(render_texture_t &wnd) override;
};

//--------------------------------------------------------------------------------------------------

inline texture_button_t::texture_button_t(const BUTTON_TEXTURE_NAME_TYPE name):
button_t(),
texture (BUTTON_TEXTURES[name])
{}

//--------------------------------------------------------------------------------------------------

inline texture_button_t::texture_button_t(const BUTTON_TEXTURE_NAME_TYPE name, const rectangle_t &region_):
button_t(region_),
texture (BUTTON_TEXTURES[name])
{}

//--------------------------------------------------------------------------------------------------

inline void texture_button_t::render(render_texture_t &wnd)
{
    wnd.draw_texture(texture, visible);
}

#endif // BUTTON_H
