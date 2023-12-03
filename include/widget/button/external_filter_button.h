#ifndef EXTERNAL_FILTER_BUTTON_H
#define EXTERNAL_FILTER_BUTTON_H

#include "label_button.h"
#include "widget/widget_container.h"
#include "widget/window/filter_param_window.h"

#include "filter/filter_manager.h"

//==================================================================================================

class external_filter_button_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline external_filter_button_controller_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager);

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

// member data
public:
    event_manager_t    & event_manager;
    widget_container_t &filter_param_window_root;
    filter_manager_t   &filter_manager;
};

//--------------------------------------------------------------------------------------------------

inline external_filter_button_controller_t::external_filter_button_controller_t(widget_container_t &root, event_manager_t &event_manager_, filter_manager_t &filter_manager_):
event_manager           (event_manager_),
filter_param_window_root(root),
filter_manager          (filter_manager_)
{}

//--------------------------------------------------------------------------------------------------

inline bool external_filter_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class external_filter_button_t: public label_button_t
{
// member functions
public:
    explicit external_filter_button_t(external_filter_button_controller_t &controller,                               const char *filter_name, FilterI *filter = nullptr);
    explicit external_filter_button_t(external_filter_button_controller_t &controller, const rectangle_t &enclosing, const char *filter_name, FilterI *filter = nullptr);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    FilterI *filter;
};

//--------------------------------------------------------------------------------------------------

inline void external_filter_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("filter_button_t", "");
}

#endif // EXTERNAL_FILTER_BUTTON_H
