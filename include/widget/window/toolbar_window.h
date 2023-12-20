#ifndef TOOLBAR_WINDOW_H
#define TOOLBAR_WINDOW_H

#include "widget/window.h"
#include "widget/button/tool_button.h"
#include "widget/button/external_tool_button.h"

#include "tool/tool_manager.h"

//==================================================================================================

class toolbar_window_t: public window_t
{
// static
public:
    static const vec2d  toolbar_size;
    static const vec2d  toolbar_btn_size;
    static const size_t toolbar_max_btns_num;
private:
    static vec2d  l_column_off;
    static vec2d  r_column_off;
    static size_t toolbar_btns_num;

// member functions
public:
    explicit toolbar_window_t(                              tool_manager_t &tool_manager, const color_t &color, const char *wnd_name);
    explicit toolbar_window_t(const rectangle_t &enclosing, tool_manager_t &tool_manager, const color_t &color, const char *wnd_name);

    void inline create        (const rectangle_t &enclosing);

    void        set_tools     (ToolI *rectangle, ToolI *ellipse);
    void        add_tool      (ToolI *tool, const char *tool_name);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    tool_button_controller_t          buttons_controller;
    external_tool_button_controller_t external_controller;

//  tool_button_t           *btn_fill;
    tool_button_t           *btn_rectangle;
    tool_button_t           *btn_ellipse;
//  tool_button_t           *btn_polyline;
//  tool_button_t           *btn_pencil;
//  tool_button_t           *btn_line;
//  tool_button_t           *btn_rubber;
//  tool_button_t           *btn_spline;
};

//--------------------------------------------------------------------------------------------------

inline void toolbar_window_t::create(const rectangle_t &enclosing_)
{
    window_t::create(enclosing_);
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void toolbar_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("toolbar_window_t", "");
}

#endif // TOOLBAR_WINDOW_H
