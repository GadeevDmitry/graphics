#ifndef PALETTE_WINDOW_H
#define PALETTE_WINDOW_H

#include "widget/window.h"
#include "widget/button/palette_button.h"
#include "tool/tool_manager.h"

//==================================================================================================

class palette_window_t: public window_t
{
// static
public:
    static const vec2d  palette_size;
    static const vec2d  palette_btn_size;
    static const size_t palette_btns_num;

// member functions
public:
    explicit palette_window_t(                              tool_manager_t &tool_manager, const color_t &color, const char *wnd_name);
    explicit palette_window_t(const rectangle_t &enclosing, tool_manager_t &tool_manager, const color_t &color, const char *wnd_name);

    void inline create        (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    palette_button_controller_t buttons_controller;
    palette_button_t           *btn_white;
    palette_button_t           *btn_blue;
    palette_button_t           *btn_red;
    palette_button_t           *btn_orange;
    palette_button_t           *btn_green;
    palette_button_t           *btn_black;
};

//--------------------------------------------------------------------------------------------------

inline void palette_window_t::create(const rectangle_t &enclosing_)
{
    window_t::create(enclosing_);
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void palette_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("palette_window_t", "");
}

#endif // PALETTE_WINDOW_H
