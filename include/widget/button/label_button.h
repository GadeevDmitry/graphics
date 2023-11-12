#ifndef LABEL_BUTTON_H
#define LABEL_BUTTON_H

#include "widget/button.h"

//==================================================================================================

class label_button_t: public button_t
{
// member functions
public:
    explicit inline label_button_t(widget_controller_t &controller,                               const char *btn_name, const color_t &background);
    explicit inline label_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const char *btn_name, const color_t &background);

// virtual
public:
    virtual void inline render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    text_t  text;
    color_t background;
};

//--------------------------------------------------------------------------------------------------

inline label_button_t::label_button_t(widget_controller_t &controller, const char *btn_name, const color_t &background_):
button_t  (controller),
text      (&font_t::get_font_by_name(font_t::EDU_QLD), btn_name),
background(background_)
{}

//--------------------------------------------------------------------------------------------------

inline label_button_t::label_button_t(widget_controller_t &controller, const rectangle_t &enclosing_, const char *btn_name, const color_t &background_):
button_t  (controller, enclosing_),
text      (&font_t::get_font_by_name(font_t::EDU_QLD), btn_name),
background(background_)
{}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(background,      own_visible);
    wnd.draw_text     (text, enclosing, own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("label_button_t", "");
}

#endif // LABEL_BUTTON_H
