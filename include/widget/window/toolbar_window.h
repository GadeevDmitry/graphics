#ifndef TOOLBAR_WINDOW_H
#define TOOLBAR_WINDOW_H

#include "widget/window.h"
#include "widget/button/tool_button.h"
#include "tool/tool_manager.h"

//==================================================================================================

class toolbar_window_t: public window_t
{
// static
public:
    static const vec2d  toolbar_size;
    static const vec2d  toolbar_btn_size;
    static const size_t toolbar_btns_num;

// member functions
public:
    explicit toolbar_window_t(window_controller_t &controller,                               tool_manager_t &tool_manager, const color_t &color, const char *wnd_name);
    explicit toolbar_window_t(window_controller_t &controller, const rectangle_t &enclosing, tool_manager_t &tool_manager, const color_t &color, const char *wnd_name);

    void        set_tools     (ToolI *fill  , ToolI *rectangle, ToolI *ellipse, ToolI *polyline,
                               ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline);
    void inline create        (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    tool_button_controller_t buttons_controller;
    tool_button_t           *btn_fill;
    tool_button_t           *btn_rectangle;
    tool_button_t           *btn_ellipse;
    tool_button_t           *btn_polyline;
    tool_button_t           *btn_pencil;
    tool_button_t           *btn_line;
    tool_button_t           *btn_rubber;
    tool_button_t           *btn_spline;
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
