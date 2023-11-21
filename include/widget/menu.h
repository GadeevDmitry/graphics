#ifndef MENU_H
#define MENU_H

#include "widget_container.h"
#include "data_structs/include/log.h"

//==================================================================================================

class menu_t: public widget_container_t
{
// member functions
public:
    explicit inline  menu_t(widget_controller_t &controller,                               const color_t &color, const bool sub_delete = false);
    explicit inline  menu_t(widget_controller_t &controller, const rectangle_t &enclosing, const color_t &color, const bool sub_delete = false);
             inline ~menu_t() {}

// virtual
public:
    virtual void inline render          (render_texture_t &wnd)                                        override;

    virtual bool        on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;
protected:
    virtual void inline dump_class_name () const override;

// member data
public:
    color_t color;
protected:
    widget_controller_t &controller;
};

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(widget_controller_t &controller_, const color_t &color_, const bool sub_delete):
widget_container_t(sub_delete),
color             (color_),
controller        (controller_)
{}

//--------------------------------------------------------------------------------------------------

inline menu_t::menu_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const color_t &color_, const bool sub_delete):
widget_container_t(enclosing_, sub_delete),
color             (color_),
controller        (controller_)
{}

//--------------------------------------------------------------------------------------------------

inline void menu_t::render(render_texture_t &wnd)
{
    wnd.draw_rectangle(color, own_visible);
    subwidgets_render(wnd);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == this, false);
    return controller.on_key_release(this, context, key);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == this, false);
    return controller.on_mouse_release(this, context, btn);
}

//--------------------------------------------------------------------------------------------------

bool menu_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    LOG_VERIFY(active == this, false);
    return controller.on_mouse_move(this, context, off);
}

//--------------------------------------------------------------------------------------------------

void menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("menu_t", "");
}

#endif // MENU_H
