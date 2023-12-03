#ifndef CANVAS_WINDOW_H
#define CANVAS_WINDOW_H

#include "widget/window.h"
#include "widget/canvas.h"

//==================================================================================================

class canvas_window_t: public window_t
{
// member functions
public:
    explicit canvas_window_t(                              tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color, const char *wnd_name);
    explicit canvas_window_t(const rectangle_t &enclosing, tool_manager_t &tool_manager, filter_manager_t &filter_manager, const color_t &color, const char *wnd_name);

    void inline create(const rectangle_t &enclosing);
private:
    void        create_canvas();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    canvas_controller_t canvas_controller;
    canvas_t           *canvas;
};

//--------------------------------------------------------------------------------------------------

inline void canvas_window_t::create(const rectangle_t &enclosing_)
{
    window_t::create(enclosing_);
    create_canvas();
}

//--------------------------------------------------------------------------------------------------

inline void canvas_window_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("canvas_window_t", "");
}

#endif // CANVAS_WINDOW_H
