#ifndef EXTERNAL_FILTER_MENU_H
#define EXTERNAL_FILTER_MENU_H

#include "widget/menu.h"
#include "widget/window.h"
#include "widget/button/label_button.h"

//==================================================================================================

class external_filter_menu_t: public menu_t
{
// member functions
public:
    explicit inline external_filter_menu_t(widget_controller_t &controller,                               const color_t &color = color_t());
    explicit inline external_filter_menu_t(widget_controller_t &controller, const rectangle_t &enclosing, const color_t &color = color_t());
};

//--------------------------------------------------------------------------------------------------

inline external_filter_menu_t::external_filter_menu_t(widget_controller_t &controller_, const color_t &color_):
menu_t(controller_, color_)
{}

//--------------------------------------------------------------------------------------------------

inline external_filter_menu_t::external_filter_menu_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const color_t &color_):
menu_t(controller_, enclosing_, color_)
{}

#endif // EXTERNAL_FILTER_MENU_H
