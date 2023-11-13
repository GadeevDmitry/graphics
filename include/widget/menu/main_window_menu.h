#ifndef MAIN_WINDOW_MENU_H
#define MAIN_WINDOW_MENU_H

#include "widget/menu.h"
#include "widget/window.h"
#include "widget/menu/external_filter_menu.h"
#include "widget/button/external_menu_button.h"

//==================================================================================================

class main_window_menu_t: public menu_t
{
// static
private:
    static const double main_menu_btn_width;

// member functions
public:
    explicit main_window_menu_t(window_controller_t &controller, filter_manager_t &filter_manager);
    explicit main_window_menu_t(window_controller_t &controller, filter_manager_t &filter_manager, const rectangle_t &enclosing);

    void inline create        (const rectangle_t &enclosing);
    void inline set_filters   (filter_t *brightness);
private:
    void        create_buttons();

// virtual
public:
    virtual void        recalc_regions ()       override;
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    external_menu_button_controller_t external_menu_button_controller;

    external_filter_menu_t filter_menu;
    external_menu_button_t filter_btn;
};

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::set_filters(filter_t *brightness)
{
    filter_menu.set_filters(brightness);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("main_window_menu_t", "");
}

#endif // MAIN_WINDOW_MENU_H
