#ifndef EXTERNAL_TOOL_MENU_H
#define EXTERNAL_TOOL_MENU_H

#include "widget/menu.h"
#include "widget/button/external_tool_button.h"

//==================================================================================================

class external_tool_menu_t: public menu_t
{
// static
public:
    static const vec2d  tool_menu_size;
    static const vec2d  tool_btn_size;
    static const size_t tool_btns_num;

// member functions
public:
    explicit external_tool_menu_t(                              tool_manager_t &tool_manager);
    explicit external_tool_menu_t(const rectangle_t &enclosing, tool_manager_t &tool_manager);

    void        set_tools(ToolI *fill  , ToolI *rectangle, ToolI *ellipse, ToolI *polyline,
                          ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline);
    void inline create   (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    external_tool_button_controller_t btn_controller;
    external_tool_button_t           *btn_fill;
    external_tool_button_t           *btn_rectangle;
    external_tool_button_t           *btn_ellipse;
    external_tool_button_t           *btn_polyline;
    external_tool_button_t           *btn_pencil;
    external_tool_button_t           *btn_line;
    external_tool_button_t           *btn_rubber;
    external_tool_button_t           *btn_spline;
};

//--------------------------------------------------------------------------------------------------

inline void external_tool_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void external_tool_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_tool_menu_t", "");
}

#endif // EXTERNAL_TOOL_MENU_H
