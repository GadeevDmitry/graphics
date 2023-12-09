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
    explicit main_window_t(                              event_manager_t &event_manager, tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color, const char *wnd_name);
    explicit main_window_t(const rectangle_t &enclosing, event_manager_t &event_manager, tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color, const char *wnd_name);

    void inline set_filters(FilterI *brightness, FilterI *russian);
    void inline set_tools  (ToolI *fill  , ToolI *rectangle, ToolI *ellipse, ToolI *polyline,
                            ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline);

    void inline add_filter (FilterI *filter, const char *filter_name);
    void inline add_tool   (ToolI   *tool  , const char *  tool_name);

    void        create     (const rectangle_t &enclosing);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    main_window_menu_t *main_menu;
};

//--------------------------------------------------------------------------------------------------

inline void main_window_t::set_filters(FilterI *brightness, FilterI *russian)
{
    main_menu->set_filters(brightness, russian);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_t::set_tools(ToolI *fill  , ToolI *rectangle, ToolI *ellipse, ToolI *polyline,
                                     ToolI *pencil, ToolI *line     , ToolI *rubber , ToolI *spline)
{
    main_menu->set_tools(fill, rectangle, ellipse, polyline, pencil, line, rubber, spline);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_t::add_filter(FilterI *filter, const char *filter_name)
{
    main_menu->add_filter(filter, filter_name);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_t::add_tool(ToolI *tool, const char *tool_name)
{
    main_menu->add_tool(tool, tool_name);
}

//--------------------------------------------------------------------------------------------------

inline void main_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("main_window_t", "");
}

#endif // MAIN_WINDOW_H
