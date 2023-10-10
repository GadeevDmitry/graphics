#ifndef WINDOW_H
#define WINDOW_H

#include "widget_manager.h"

//==================================================================================================

class window_t: public widget_manager_t
{
protected:
    rectangle_t area;

public:
    inline          window_t();
    inline explicit window_t(const rectangle_t &area_, widget_t *parent_);

    inline void set_area(const rectangle_t &area_);

    virtual inline bool on_key_press  (const KEY_TYPE &key) override;
    virtual inline bool on_key_release(const KEY_TYPE &key) override;

    virtual inline bool on_mouse_press  (const mouse_context_t &context) override;
    virtual inline bool on_mouse_release(const mouse_context_t &context) override;
};

//--------------------------------------------------------------------------------------------------

inline window_t::window_t():
area()
{}

//--------------------------------------------------------------------------------------------------

inline window_t::window_t(const rectangle_t &area_, widget_t *parent_):
widget_manager_t(area_, parent_),
area            (area_)
{}

//--------------------------------------------------------------------------------------------------

inline void window_t::set_area(const rectangle_t &area_)
{
    area = area_;
}

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_key_press  (const KEY_TYPE &key) { return false; }
inline bool window_t::on_key_release(const KEY_TYPE &key) { return false; }

//--------------------------------------------------------------------------------------------------

inline bool window_t::on_mouse_press  (const mouse_context_t &context) { return false; }
inline bool window_t::on_mouse_release(const mouse_context_t &context) { return false; }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class color_window_t: public window_t
{
public:
    color_t color;

    inline          color_window_t();
    inline explicit color_window_t(const rectangle_t &area_, const color_t &color_, widget_t *parent_);
    inline         ~color_window_t() {}

    virtual inline void render(render_texture_t &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t():
color()
{}

//--------------------------------------------------------------------------------------------------

inline color_window_t::color_window_t(const rectangle_t &area_, const color_t &color_, widget_t *parent_):
window_t(area_, parent_),
color   (color_)
{}

//--------------------------------------------------------------------------------------------------

void color_window_t::render(render_texture_t &wnd) const
{


    // wnd.draw_filled_rectangle(area, color);
    rectangle_t rect = rectangle_t(vec2d(300, 400), vec2d(200, 300));
    clipping_region_t reg = clipping_region_t();
    reg.push_area(rect);
    
    wnd.draw_filled_rectangle(rect, color);
    wnd.draw_line(segment_t(vec2d(10, 0), vec2d(300, 400)), color_t(255, 255, 255), reg);
    widgets_render(wnd);
}

#endif // WINDOW_H
