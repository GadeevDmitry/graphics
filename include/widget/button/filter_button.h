#ifndef FILTER_BUTTON_H
#define FILTER_BUTTON_H

#include "label_button.h"
#include "filter/filter_manager.h"

//==================================================================================================

class filter_button_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline filter_button_controller_t(filter_manager_t &filter_manager);

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

// member data
public:
    filter_manager_t &filter_manager;
};

//--------------------------------------------------------------------------------------------------

inline filter_button_controller_t::filter_button_controller_t(filter_manager_t &filter_manager_):
filter_manager(filter_manager_)
{}

//--------------------------------------------------------------------------------------------------

inline bool filter_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class filter_button_t: public label_button_t
{
// member functions
public:
    explicit filter_button_t(widget_controller_t &controller,                               const char *filter_name, FilterI *filter = nullptr);
    explicit filter_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const char *filter_name, FilterI *filter = nullptr);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    FilterI *filter;
};

//--------------------------------------------------------------------------------------------------

inline void filter_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("filter_button_t", "");
}

#endif // FILTER_BUTTON_H
