#ifndef EXTERNAL_TOOL_BUTTON_H
#define EXTERNAL_TOOL_BUTTON_H

#include "label_button.h"
#include "tool/tool_manager.h"

//==================================================================================================

class external_tool_button_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline external_tool_button_controller_t(tool_manager_t &tool_manager);

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

// member data
private:
    tool_manager_t &tool_manager;
};

//--------------------------------------------------------------------------------------------------

inline external_tool_button_controller_t::external_tool_button_controller_t(tool_manager_t &tool_manager_):
tool_manager(tool_manager_)
{}

//--------------------------------------------------------------------------------------------------

inline bool external_tool_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class external_tool_button_t: public label_button_t
{
// member functions
public:
    explicit inline external_tool_button_t(widget_controller_t &controller,                               const char *tool_name, ToolI *tool = nullptr);
    explicit inline external_tool_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const char *tool_name, ToolI *tool = nullptr);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    ToolI *tool;
};

//--------------------------------------------------------------------------------------------------

inline external_tool_button_t::external_tool_button_t(widget_controller_t &controller_, const char *tool_name, ToolI *tool_):
label_button_t(controller_, tool_name, 20),
tool          (tool_)
{}

//--------------------------------------------------------------------------------------------------

inline external_tool_button_t::external_tool_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const char *tool_name, ToolI *tool_):
label_button_t(controller_, enclosing_, tool_name, 20),
tool          (tool_)
{}

//--------------------------------------------------------------------------------------------------

inline void external_tool_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_tool_button_t", "");
}

#endif // EXTERNAL_TOOL_BUTTON_H
