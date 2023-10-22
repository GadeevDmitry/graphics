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
    explicit palette_window_t(window_controller_t &controller, tool_manager_t &tool_manager,                               const color_t &color = Red_theme);
    explicit palette_window_t(window_controller_t &controller, tool_manager_t &tool_manager, const rectangle_t &enclosing, const color_t &color = Red_theme);

    void inline create        (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// member data
private:
    palette_button_controller_t buttons_controller;
    palette_button_t            btn_white;
    palette_button_t            btn_blue;
    palette_button_t            btn_red;
    palette_button_t            btn_orange;
    palette_button_t            btn_green;
    palette_button_t            btn_black;
};

//--------------------------------------------------------------------------------------------------

inline void palette_window_t::create(const rectangle_t &enclosing)
{
    window_t::create(enclosing);
    create_buttons();
}

#endif // PALETTE_WINDOW_H
