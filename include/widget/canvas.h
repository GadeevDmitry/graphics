#ifndef CANVAS_H
#define CANVAS_H

#include "widget.h"
#include "data_structs/include/log.h"

//==================================================================================================

class tool_manager_t;

class canvas_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline canvas_controller_t(tool_manager_t &tool_manager);

// virtual
public:
    virtual bool on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_move   (widget_t *handle, const eventable::mouse_context_t &context, const vec2d             &off) override;

// member data
private:
    tool_manager_t &tool_manager;
};

//--------------------------------------------------------------------------------------------------

inline canvas_controller_t::canvas_controller_t(tool_manager_t &tool_manager_):
tool_manager(tool_manager_)
{}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class canvas_t: public widget_t
{
// member functions
public:
    explicit inline canvas_t(widget_controller_t &controller);
    explicit inline canvas_t(widget_controller_t &controller, const rectangle_t &enclosing, const color_t &background = color_t::White);

    void inline create         (const rectangle_t &enclosing, const color_t &background = color_t::White);
private:
    void        create_textures(const color_t &background);

// virtual
public:
    virtual void        render          (render_texture_t &wnd)                                        override;

    virtual bool inline on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override; 
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;

// member data
protected:
    render_texture_t perm;
    render_texture_t temp;

    widget_controller_t &controller;

// friends
    friend canvas_controller_t;
};

//--------------------------------------------------------------------------------------------------

inline canvas_t::canvas_t(widget_controller_t &controller_):
widget_t  (),
perm      (),
temp      (),
controller(controller_)
{}

//--------------------------------------------------------------------------------------------------

inline canvas_t::canvas_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const color_t &background):
widget_t  (enclosing_),
perm      (),
temp      (),
controller(controller_)
{
    create_textures(background);
}

//--------------------------------------------------------------------------------------------------

inline void canvas_t::create(const rectangle_t &enclosing, const color_t &background)
{
    visible.enclosing = enclosing;
    create_textures(background);
}

//--------------------------------------------------------------------------------------------------

inline bool canvas_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == nullptr, false);
    return controller.on_key_press(this, context, key);
}

//--------------------------------------------------------------------------------------------------

inline bool canvas_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == this, false);
    return controller.on_key_release(this, context, key);
}

//--------------------------------------------------------------------------------------------------

inline bool canvas_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == this, false);
    return controller.on_mouse_release(this, context, btn);
}

//--------------------------------------------------------------------------------------------------

inline bool canvas_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    LOG_VERIFY(active == this, false);
    return controller.on_mouse_move(this, context, off);
}

#endif // CANVAS_H
