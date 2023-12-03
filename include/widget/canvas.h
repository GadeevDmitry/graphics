#ifndef CANVAS_H
#define CANVAS_H

#include "button.h"
#include "data_structs/include/log.h"

//==================================================================================================

class tool_manager_t;
class filter_manager_t;

class canvas_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline canvas_controller_t(tool_manager_t &tool_manager, filter_manager_t &filter_manager);

// virtual
public:
    virtual bool on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_move   (widget_t *handle, const eventable::mouse_context_t &context, const vec2d             &off) override;

// member data
private:
    tool_manager_t   &tool_manager;
    filter_manager_t &filter_manager;
};

//--------------------------------------------------------------------------------------------------

inline canvas_controller_t::canvas_controller_t(tool_manager_t &tool_manager_, filter_manager_t &filter_manager_):
tool_manager  (tool_manager_),
filter_manager(filter_manager_)
{}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class canvas_t: public button_t
{
// types
public:
    enum CANVAS_INSTRUMENT_TYPE
    {
        TOOL,
        FILTER,
    };

// static
public:
    static CANVAS_INSTRUMENT_TYPE active_instrument;

// member functions
public:
    explicit inline canvas_t(canvas_controller_t &controller);
    explicit inline canvas_t(canvas_controller_t &controller, const rectangle_t &enclosing, const color_t &background = color_t::White);

    void inline create         (const rectangle_t &enclosing, const color_t &background = color_t::White);
private:
    void        create_textures(const color_t &background);

// virtual
public:
    virtual void render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
protected:
    render_texture_t perm;
    render_texture_t temp;

// friends
    friend canvas_controller_t;
};

//--------------------------------------------------------------------------------------------------

inline canvas_t::canvas_t(canvas_controller_t &controller_):
button_t  (controller_),
perm      (),
temp      ()
{}

//--------------------------------------------------------------------------------------------------

inline canvas_t::canvas_t(canvas_controller_t &controller_, const rectangle_t &enclosing_, const color_t &background):
button_t  (controller_, enclosing_),
perm      (),
temp      ()
{
    create_textures(background);
}

//--------------------------------------------------------------------------------------------------

inline void canvas_t::create(const rectangle_t &enclosing_, const color_t &background)
{
    enclosing = enclosing_;
    create_textures(background);
}

//--------------------------------------------------------------------------------------------------

inline void canvas_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("canvas_t", "");
}

#endif // CANVAS_H
