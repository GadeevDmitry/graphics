#ifndef CANVAS_WINDOW_H
#define CANVAS_WINDOW_H

#include "widget/window.h"
#include "widget/canvas.h"

//==================================================================================================

class canvas_window_t: public window_t
{
// member functions
public:
    explicit canvas_window_t(window_controller_t &controller, tool_manager_t &tool_manager,                               const char *header_name, const color_t &color = Red_theme);
    explicit canvas_window_t(window_controller_t &controller, tool_manager_t &tool_manager, const rectangle_t &enclosing, const char *header_name, const color_t &color = Red_theme);

    void inline create(const rectangle_t &enclosing);
private:
    void        create_canvas();

// virtual
protected:
    void inline dump_class_name() const override;

// member data
private:
    canvas_controller_t canvas_controller;
    canvas_t            canvas;
};

//--------------------------------------------------------------------------------------------------

inline void canvas_window_t::create(const rectangle_t &enclosing)
{
    window_t::create(enclosing);
    create_canvas();
}

//--------------------------------------------------------------------------------------------------

inline void canvas_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("canvas_window_t", "");
}

#endif // CANVAS_WINDOW_H
