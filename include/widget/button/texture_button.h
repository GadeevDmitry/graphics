#ifndef TEXTURE_BUTTON_H
#define TEXTURE_BUTTON_H

#include "widget/button.h"

//==================================================================================================

class texture_button_t: public button_t
{
// member functions
public:
    explicit inline texture_button_t(widget_controller_t &controller,                               const texture_t *texture = nullptr);
    explicit inline texture_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const texture_t *texture = nullptr);

// virtual
public:
    virtual void inline render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    const texture_t *texture;
};

//--------------------------------------------------------------------------------------------------

inline texture_button_t::texture_button_t(widget_controller_t &controller_, const texture_t *texture_):
button_t(controller_),
texture (texture_)
{}

//--------------------------------------------------------------------------------------------------

inline texture_button_t::texture_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const texture_t *texture_):
button_t(controller_, enclosing_),
texture (texture_)
{}

//--------------------------------------------------------------------------------------------------

inline void texture_button_t::render(render_texture_t &wnd)
{
    wnd.draw_texture(*texture, enclosing, own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void texture_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("texture_button_t", "");
}

#endif // TEXTURE_BUTTON_H
