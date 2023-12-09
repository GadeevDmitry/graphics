#ifndef MAIN_WINDOW_MENU_H
#define MAIN_WINDOW_MENU_H

#include "external_tool_menu.h"
#include "external_filter_menu.h"
#include "external_palette_menu.h"
#include "widget/window.h"
#include "widget/button/external_menu_button.h"

//==================================================================================================

class main_window_menu_t: public menu_t
{
// static
private:
    static const double main_menu_btn_width;

// member functions
public:
    explicit main_window_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager, tool_manager_t &tool_manager);
    explicit main_window_menu_t(widget_container_t &root, event_manager_t &event_manager, filter_manager_t &filter_manager, tool_manager_t &tool_manager, const rectangle_t &enclosing);

    void inline create        (const rectangle_t &enclosing);
    void inline set_filters   (FilterI *brightness, FilterI *russian);
    void inline set_tools     (ToolI *fill  , ToolI *rectangle, ToolI *ellipse, ToolI *polyline,
                               ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline);

    void inline add_filter    (FilterI *filter, const char *filter_name);
    void inline add_tool      (ToolI   *tool  , const char *  tool_name);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
public:
    virtual void        recalc_regions ()       override;
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    external_filter_menu_t  filter_menu;
    external_tool_menu_t    tool_menu;
    external_palette_menu_t palette_menu;

    external_menu_button_t  filter_btn;
    external_menu_button_t  tool_btn;
    external_menu_button_t  palette_btn;
};

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::set_filters(FilterI *brightness, FilterI *russian)
{
    filter_menu.set_filters(brightness, russian);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::set_tools(ToolI *fill  , ToolI *rectangle, ToolI *ellipse, ToolI *polyline,
                                          ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline)
{
    tool_menu.set_tools(fill, rectangle, ellipse, polyline, pencil, line, rubber, spline);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::add_filter(FilterI *filter, const char *filter_name)
{
    filter_menu.add_filter(filter, filter_name);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::add_tool(ToolI *tool, const char *tool_name)
{
    tool_menu.add_tool(tool, tool_name);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("main_window_menu_t", "");
}

#endif // MAIN_WINDOW_MENU_H
