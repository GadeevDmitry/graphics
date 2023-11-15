#ifndef LABEL_BUTTON_H
#define LABEL_BUTTON_H

#include "widget/button.h"

//==================================================================================================

class label_button_t: public button_t
{
// member functions
public:
    explicit label_button_t(widget_controller_t &controller);
    explicit label_button_t(widget_controller_t &controller, const rectangle_t &enclosing);
    explicit label_button_t(widget_controller_t &controller,                               const char *btn_name, const size_t char_size);
    explicit label_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const char *btn_name, const size_t char_size);

    void create_texture();

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
    color_t border_color;
private:
    texture_t texture;
};

//--------------------------------------------------------------------------------------------------

inline void label_button_t::render(render_texture_t &wnd)
{
    wnd.draw_texture(texture, enclosing, own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void label_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("label_button_t", "");
}

#endif // LABEL_BUTTON_H
