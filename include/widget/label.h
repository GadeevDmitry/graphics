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
    explicit inline label_t(                              const text_t &text, const color_t &background, const vec2d &text_rel_off = vec2d(0, 0));
    explicit inline label_t(const rectangle_t &enclosing, const text_t &text, const color_t &background, const vec2d &text_rel_off = vec2d(0, 0));

// virtual
public:
    virtual void inline render          (render_texture_t &wnd)                                        override;

    virtual bool inline on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;
protected:
    virtual void inline dump_class_name () const override;

// member data
public:
    text_t  text;
    vec2d   text_rel_off;
    color_t background;
};

//--------------------------------------------------------------------------------------------------

inline label_t::label_t():
widget_t    (),
text        (),
text_rel_off(0, 0),
background  ()
{}

//--------------------------------------------------------------------------------------------------

inline label_t::label_t(const text_t &text_, const color_t &background_, const vec2d &text_rel_off_):
widget_t    (),
text        (text_),
text_rel_off(text_rel_off_),
background  (background_)
{}

//--------------------------------------------------------------------------------------------------

inline label_t::label_t(const rectangle_t &enclosing_, const text_t &text_, const color_t &background_, const vec2d &text_rel_off_):
widget_t    (enclosing_),
text        (text_),
text_rel_off(text_rel_off_),
background  (background_)
{}

//--------------------------------------------------------------------------------------------------

inline void label_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(background,                          own_visible);
    wnd.draw_text     (text      , text_rel_off, enclosing, own_visible);
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

//--------------------------------------------------------------------------------------------------

inline void label_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("label_t", "");
}

#endif // LABEL_H
