#ifndef EXTERNAL_CANVAS_MENU_H
#define EXTERNAL_CANVAS_MENU_H

#include "widget/menu.h"
#include "widget/button/external_canvas_button.h"

//==================================================================================================

class external_canvas_menu_t: public menu_t
{
// static
public:
    static const vec2d  canvas_menu_size;
    static const vec2d  canvas_btn_size;
    static const size_t canvas_btns_num;

// member functions
public:
    explicit external_canvas_menu_t();
    explicit external_canvas_menu_t(const rectangle_t &enclosing);

    void     inline create(const rectangle_t &enclosing);
    void   register_canvas(canvas_window_t *canvas_wnd, const char *canvas_name);
    void unregister_canvas(canvas_window_t *canvas_wnd);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    external_canvas_button_controller_t btn_controller;
};

//--------------------------------------------------------------------------------------------------

inline void external_canvas_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
}

//--------------------------------------------------------------------------------------------------

inline void external_canvas_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_canvas_menu_t", "");
}

#endif // EXTERNAL_CANVAS_MENU_H
