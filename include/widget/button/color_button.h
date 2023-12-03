#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

#include "widget/button.h"

//==================================================================================================

class color_button_t: public button_t
{
// member functions
public:
    explicit color_button_t(widget_controller_t &controller);
    explicit color_button_t(widget_controller_t &controller, const rectangle_t &enclosing);
    explicit color_button_t(widget_controller_t &controller,                               const color_t &border, const color_t &background);
    explicit color_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const color_t &border, const color_t &background);

    void create_texture();

// virtual
public:
    virtual void inline render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    color_t border;
    color_t background;
private:
    texture_t texture;
};

//--------------------------------------------------------------------------------------------------

inline void color_button_t::render(render_texture_t &wnd)
{
    wnd.draw_texture(texture, enclosing, own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void color_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("color_button_t", "");
}

#endif // COLOR_BUTTON_H
