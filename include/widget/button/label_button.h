#ifndef LABEL_BUTTON_H
#define LABEL_BUTTON_H

#include "widget/button.h"

//==================================================================================================

class label_button_t: public button_t
{
// member functions
public:
    explicit inline label_button_t(widget_controller_t &controller,                               const char *btn_name, const size_t &char_size);
    explicit inline label_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const char *btn_name, const size_t &char_size);

// virtual
public:
    virtual void inline render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    text_t  text;
};

//--------------------------------------------------------------------------------------------------

inline label_button_t::label_button_t(widget_controller_t &controller_, const char *btn_name, const size_t &char_size):
button_t    (controller_),
text        (&font_t::get_font_by_name(font_t::EDU_QLD), btn_name, color_t::Black, char_size)
{}

//--------------------------------------------------------------------------------------------------

inline label_button_t::label_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const char *btn_name, const size_t &char_size):
button_t    (controller_, enclosing_),
text        (&font_t::get_font_by_name(font_t::EDU_QLD), btn_name, color_t::Black, char_size)
{}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(color_t::White,               own_visible);
    wnd.draw_text     (text, vec2d(5, 5), enclosing, own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("label_button_t", "");
}

#endif // LABEL_BUTTON_H
