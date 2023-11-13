#ifndef LABEL_BUTTON_H
#define LABEL_BUTTON_H

#include "widget/button.h"

//==================================================================================================

class label_button_t: public button_t
{
// member functions
public:
    explicit inline label_button_t(widget_controller_t &controller,                               const text_t &text, const color_t &background, const vec2d &text_rel_off = vec2d(0, 0));
    explicit inline label_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const text_t &text, const color_t &background, const vec2d &text_rel_off = vec2d(0, 0));

// virtual
public:
    virtual void inline render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    text_t  text;
    vec2d   text_rel_off;
    color_t background;
};

//--------------------------------------------------------------------------------------------------

inline label_button_t::label_button_t(widget_controller_t &controller, const text_t &text_, const color_t &background_, const vec2d &text_rel_off_):
button_t    (controller),
text        (text_),
text_rel_off(text_rel_off_),
background  (background_)
{}

//--------------------------------------------------------------------------------------------------

inline label_button_t::label_button_t(widget_controller_t &controller, const rectangle_t &enclosing_, const text_t &text_, const color_t &background_, const vec2d &text_rel_off_):
button_t    (controller, enclosing_),
text        (text_),
text_rel_off(text_rel_off_),
background  (background_)
{}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(background,                    own_visible);
    wnd.draw_text     (text, text_rel_off, enclosing, own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("label_button_t", "");
}

#endif // LABEL_BUTTON_H
