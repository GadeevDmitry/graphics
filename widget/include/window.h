#ifndef WINDOW_H
#define WINDOW_H

#include "widget.h"
#include "texture.h"
#include "list.h"

//==================================================================================================

class window_t: public widget_t
{
protected:
    rectangle_t area;
    list        sub_widgets;

    inline bool is_mouse_inside   (const vec2d &pos);
    void        render_sub_widgets(render_texture_t &wnd) const;

public:
    inline          window_t();
    inline explicit window_t(const rectangle_t &area_);
    inline         ~window_t();

    inline void set_area       (const rectangle_t &area_);
    inline bool register_widget(const widget_t *sub_widget);

    virtual inline bool on_key_press  (const KEY_TYPE key) override;
    virtual inline bool on_key_release(const KEY_TYPE key) override;

    virtual inline bool on_mouse_press  (const vec2d &pos, const MOUSE_BUTTON_TYPE btn) override;
    virtual inline bool on_mouse_release(const vec2d &pos, const MOUSE_BUTTON_TYPE btn) override;

private:
    bool on_key_event  (key_event   event, KEY_TYPE key);
    bool on_mouse_event(mouse_event event, const vec2d &pos, const MOUSE_BUTTON_TYPE btn);
};

//--------------------------------------------------------------------------------------------------

inline bool window_t::is_mouse_inside(const vec2d &pos) { return area.is_point_inside(pos); }

//--------------------------------------------------------------------------------------------------

inline window_t::window_t():
widget_t(),
area    ()
{
    list_ctor(&sub_widgets, sizeof(widget_t *), widget_delete);
}

//--------------------------------------------------------------------------------------------------

inline window_t::window_t(const rectangle_t &area_):
widget_t(),
area    (area_)
{
    list_ctor(&sub_widgets, sizeof(widget_t *), widget_delete);
}

//--------------------------------------------------------------------------------------------------

inline window_t::~window_t()
{
    list_dtor(&sub_widgets);
}

//--------------------------------------------------------------------------------------------------

inline void window_t::set_area(const rectangle_t &area_)
{
    area = area_;
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::register_widget(const widget_t *sub_widget)
{
    return list_push_front(&sub_widgets, &sub_widget);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_press(const KEY_TYPE key)
{
    return on_key_event(&widget_t::on_key_press, key);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_release(const KEY_TYPE key)
{
    return on_key_event(&widget_t::on_key_release, key);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_mouse_press(const vec2d &pos, const MOUSE_BUTTON_TYPE btn)
{
    return on_mouse_event(&widget_t::on_mouse_press, pos, btn);
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_mouse_release(const vec2d &pos, const MOUSE_BUTTON_TYPE btn)
{
    return on_mouse_event(&widget_t::on_mouse_release, pos, btn);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class texture_window_t: public window_t
{
public:
    texture_t texture;

    inline          texture_window_t();
    inline explicit texture_window_t(const rectangle_t &area_, const char *filename_);
    inline explicit texture_window_t(const rectangle_t &area_, const unsigned width_, const unsigned height_);
    inline         ~texture_window_t() {}

    virtual void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline texture_window_t::texture_window_t():
window_t(),
texture ()
{}

//--------------------------------------------------------------------------------------------------

inline texture_window_t::texture_window_t(const rectangle_t &area_, const char *filename_):
window_t(area_),
texture (filename_)
{}

//--------------------------------------------------------------------------------------------------

inline texture_window_t::texture_window_t(const rectangle_t &area_, const unsigned width_, const unsigned height_):
window_t(area_),
texture (width_, height_)
{}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_window_t: public window_t
{
public:
    color_t color;

    inline          color_window_t();
    inline explicit color_window_t(const rectangle_t &area_, const color_t &color_);
    inline         ~color_window_t() {}

    virtual void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t():
window_t(),
color   ()
{}

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t(const rectangle_t &area_, const color_t &color_):
window_t(area_),
color   (color_)
{}

#endif // WINDOW_H
