#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "widget/window.h"
#include "widget/menu/main_window_menu.h"

//==================================================================================================

class main_window_t: public window_t
{
// static
public:
    static const double main_menu_height;

// member functions
public:
    explicit main_window_t(window_controller_t &controller, filter_manager_t &filter_manager,                               const char *header_name, const color_t &color = Red_theme);
    explicit main_window_t(window_controller_t &controller, filter_manager_t &filter_manager, const rectangle_t &enclosing, const char *header_name, const color_t &color = Red_theme);

    void        create     (const rectangle_t &enclosing);
    void inline set_filters(filter_t *brightness);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    main_window_menu_t main_menu;
};

//--------------------------------------------------------------------------------------------------

inline void main_window_t::set_filters(filter_t *brightness)
{
    main_menu.set_filters(brightness);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("main_window_t", "");
}

#endif // MAIN_WINDOW_H
