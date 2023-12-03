#ifndef EXTERNAL_FILTER_MENU_H
#define EXTERNAL_FILTER_MENU_H

#include "widget/menu.h"
#include "widget/button/external_filter_button.h"

//==================================================================================================

class external_filter_menu_t: public menu_t
{
// static
public:
    static const vec2d  filter_menu_size;
    static const vec2d  filter_btn_size;
    static const size_t filter_btns_num;

// member functions
public:
    explicit external_filter_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager);
    explicit external_filter_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager, const rectangle_t &enclosing);

    void inline set_filters(FilterI *brightness);
    void inline create     (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    external_filter_button_controller_t btn_controller;
    external_filter_button_t           *btn_brightness;
};

//--------------------------------------------------------------------------------------------------

inline void external_filter_menu_t::set_filters(FilterI *brightness)
{
    btn_brightness->filter = brightness;
}

//--------------------------------------------------------------------------------------------------

inline void external_filter_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void external_filter_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_filter_menu_t", "");
}

#endif // EXTERNAL_FILTER_MENU_H
