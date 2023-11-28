#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H

#include "widget/button/texture_button.h"
#include "tool/tool_manager.h"

//==================================================================================================

class tool_button_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline tool_button_controller_t(tool_manager_t &tool_manager);

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

// member data
private:
    tool_manager_t &tool_manager;
};

//--------------------------------------------------------------------------------------------------

inline tool_button_controller_t::tool_button_controller_t(tool_manager_t &tool_manager_):
tool_manager(tool_manager_)
{}

//--------------------------------------------------------------------------------------------------

inline bool tool_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class tool_button_t: public texture_button_t
{
// types
public:
    enum BUTTON_TEXTURE_NAME_TYPE
    {
        BUTTON_TEXTURE_NAME_TYPE_UNKNOWN = -1,

        FILL_ON,
        RECTANGLE_ON,
        ELLIPSE_ON,
        POLYLINE_ON,
        PENCIL_ON,
        LINE_ON,
        RUBBER_ON,
        SPLINE_ON,

        FILL_OFF,
        RECTANGLE_OFF,
        ELLIPSE_OFF,
        POLYLINE_OFF,
        PENCIL_OFF,
        LINE_OFF,
        RUBBER_OFF,
        SPLINE_OFF,

        BUTTON_TEXTURE_NAME_COUNT
    };

// static
public:
    static void load_textures();
private:
    static texture_t   BUTTON_TEXTURES[];
    static const char *BUTTON_TEXTURES_FILES[];

// member functions
public:
    explicit inline tool_button_t(widget_controller_t &controller,                               const BUTTON_TEXTURE_NAME_TYPE &texture, ToolI *tool = nullptr);
    explicit inline tool_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const BUTTON_TEXTURE_NAME_TYPE &texture, ToolI *tool = nullptr);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    ToolI *tool;
};

//--------------------------------------------------------------------------------------------------

inline tool_button_t::tool_button_t(widget_controller_t &controller_, const BUTTON_TEXTURE_NAME_TYPE &texture_, ToolI *tool_):
texture_button_t(controller_),
tool            (tool_)
{
    LOG_VERIFY(texture_ > BUTTON_TEXTURE_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(texture_ < BUTTON_TEXTURE_NAME_COUNT       , ;);
    texture = BUTTON_TEXTURES + texture_;
}

//--------------------------------------------------------------------------------------------------

inline tool_button_t::tool_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const BUTTON_TEXTURE_NAME_TYPE &texture_, ToolI *tool_):
texture_button_t(controller_, enclosing_),
tool            (tool_)
{
    LOG_VERIFY(texture_ > BUTTON_TEXTURE_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(texture_ < BUTTON_TEXTURE_NAME_COUNT       , ;);
    texture = BUTTON_TEXTURES + texture_;
}

//--------------------------------------------------------------------------------------------------

inline void tool_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("tool_button_t", "");
}

#endif // TOOL_BUTTON_H
