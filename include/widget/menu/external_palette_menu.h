#ifndef EXTERNAL_PALETTE_MENU_H
#define EXTERNAL_PALETTE_MENU_H

#include "widget/menu.h"
#include "widget/button/external_palette_button.h"

//==================================================================================================

class external_palette_menu_t: public menu_t
{
// static
public:
    static const vec2d  palette_menu_size;
    static const vec2d  palette_btn_size;
    static const size_t palette_btns_num;

// member functions
public:
    explicit external_palette_menu_t(widget_controller_t &controller,                               tool_manager_t &tool_manager);
    explicit external_palette_menu_t(widget_controller_t &controller, const rectangle_t &enclosing, tool_manager_t &tool_manager);

    void inline create   (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    external_palette_button_controller_t buttons_controller;
    external_palette_button_t           *btn_white;
    external_palette_button_t           *btn_blue;
    external_palette_button_t           *btn_red;
    external_palette_button_t           *btn_orange;
    external_palette_button_t           *btn_green;
    external_palette_button_t           *btn_black;
};

//--------------------------------------------------------------------------------------------------

inline void external_palette_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void external_palette_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_palette_menu_t", "");
}

#endif // EXTERNAL_PALETTE_MENU_H
