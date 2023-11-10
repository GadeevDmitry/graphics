#ifndef LABEL_H
#define LABEL_H

#include "graphic/text.h"
#include "widget/widget.h"

//==================================================================================================

class label_t: public widget_t
{
// member functions
public:
             inline label_t();
    explicit inline label_t(                              const text_t &text, const color_t &background);
    explicit inline label_t(const rectangle_t &enclosing, const text_t &text, const color_t &background);

// virtual
public:
    virtual void inline render          (render_texture_t &wnd)                                        override;

    virtual bool inline on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;

// member data
public:
    text_t  text;
    color_t background;
};

//--------------------------------------------------------------------------------------------------

inline label_t::label_t():
widget_t  (),
text      (),
background()
{}

//--------------------------------------------------------------------------------------------------

inline label_t::label_t(const text_t &text_, const color_t &background_):
widget_t  (),
text      (text_),
background(background_)
{}

//--------------------------------------------------------------------------------------------------

inline label_t::label_t(const rectangle_t &enclosing, const text_t &text_, const color_t &background_):
widget_t  (enclosing),
text      (text_),
background(background_)
{}

//--------------------------------------------------------------------------------------------------

inline void label_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(background, visible);
    wnd.draw_text     (text      , visible);
}

//--------------------------------------------------------------------------------------------------

inline bool label_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    (void) context;
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool label_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    (void) context;
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool label_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool label_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool label_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    (void) context;
    (void) off;
    return false;
}

#endif // LABEL_H
