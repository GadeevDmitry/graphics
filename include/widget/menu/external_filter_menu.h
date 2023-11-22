#ifndef EXTERNAL_FILTER_MENU_H
#define EXTERNAL_FILTER_MENU_H

#include "widget/menu.h"
#include "widget/window.h"
#include "widget/button/filter_button.h"

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
    explicit external_filter_menu_t(widget_controller_t &controller,                               filter_manager_t &filter_manager);
    explicit external_filter_menu_t(widget_controller_t &controller, const rectangle_t &enclosing, filter_manager_t &filter_manager);

    void inline set_filters(filter_t *brightness);
    void inline create     (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    filter_button_controller_t buttons_controller;
    filter_button_t           *btn_brightness;
};

//--------------------------------------------------------------------------------------------------

inline void external_filter_menu_t::set_filters(filter_t *brightness)
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
