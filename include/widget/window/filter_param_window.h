#ifndef PARAM_WINDOW_H
#define PARAM_WINDOW_H

#include "modal_window.h"
#include "widget/button/edit_box.h"
#include "widget/button/label_button.h"

#include "plugin/standart/Filter.h"
#include "data_structs/include/array.h"

//==================================================================================================

using plugin::FilterI;

class filter_param_window_t;
class apply_button_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline apply_button_controller_t(filter_param_window_t &param_wnd);

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

// member data
public:
    filter_param_window_t &param_wnd;
};

//--------------------------------------------------------------------------------------------------

inline apply_button_controller_t::apply_button_controller_t(filter_param_window_t &param_wnd_):
param_wnd(param_wnd_)
{}

//--------------------------------------------------------------------------------------------------

inline bool apply_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class filter_param_window_t: public modal_window_t
{
// static
private:
    static const vec2d content_ld_off;
    static const vec2d content_ru_off;

    static const double edit_box_off;
    static const double edit_box_width;

    static const double string_height;
    static const double hollow_height;

// member functions
public:
    explicit filter_param_window_t(event_manager_t &event_manager,                                    const char *wnd_name, FilterI *filter = nullptr);
    explicit filter_param_window_t(event_manager_t &event_manager, const rectangle_t &root_enclosing, const char *wnd_name, FilterI *filter);
    inline  ~filter_param_window_t();

    void create(const rectangle_t &root_enclosing, FilterI *filter = nullptr);
private:
    void create_params   (const size_t param_num, const double param_name_width);
    void create_apply_btn();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    apply_button_controller_t apply_btn_controller;
    label_button_t           *apply_btn;

    FilterI                  *filter;
    array                     edit_boxes;

// friends
    friend apply_button_controller_t;
};

//--------------------------------------------------------------------------------------------------

inline filter_param_window_t::~filter_param_window_t()
{
    array_dtor(&edit_boxes);
}

//--------------------------------------------------------------------------------------------------

inline void filter_param_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("filter_param_window_t", "");
}

#endif // PARAM_WINDOW_H
