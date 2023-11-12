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
    explicit toolbar_window_t(window_controller_t &controller, tool_manager_t &tool_manager,                               const char *header_name, const color_t &color = Red_theme);
    explicit toolbar_window_t(window_controller_t &controller, tool_manager_t &tool_manager, const rectangle_t &enclosing, const char *header_name, const color_t &color = Red_theme);

    void        set_tools     (tool_t *fill  , tool_t *rectangle, tool_t *ellipse, tool_t *polyline,
                               tool_t *pencil, tool_t *line     , tool_t *rubber , tool_t *spline);
    void inline create        (const rectangle_t &enclosing);
private:
    void        create_buttons();
    void      register_buttons();

// virtual
protected:
    void inline dump_class_name() const override;

// member data
private:
    tool_button_controller_t buttons_controller;
    tool_button_t            btn_fill;
    tool_button_t            btn_rectangle;
    tool_button_t            btn_ellipse;
    tool_button_t            btn_polyline;
    tool_button_t            btn_pencil;
    tool_button_t            btn_line;
    tool_button_t            btn_rubber;
    tool_button_t            btn_spline;
};

//--------------------------------------------------------------------------------------------------

inline void toolbar_window_t::create(const rectangle_t &enclosing)
{
    window_t::create(enclosing);
    create_buttons();
}

//--------------------------------------------------------------------------------------------------

inline void toolbar_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("toolbar_window_t", "");
}

#endif // TOOLBAR_WINDOW_H
