#ifndef WINDOW_HEADER_MENU_H
#define WINDOW_HEADER_MENU_H

#include "widget/menu.h"
#include "widget/label.h"
#include "widget/button/close_button.h"

//==================================================================================================

class window_header_menu_controller_t: public widget_controller_t
{
// virtual
public:
    virtual bool on_mouse_move(widget_t *handle, const eventable::mouse_context_t &context, const vec2d &off) override;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class window_t;
class window_header_menu_t: public menu_t
{
// static
public:
    static window_header_menu_controller_t window_header_menu_controller;

// member functions
public:
    explicit window_header_menu_t(                              window_t &wnd, const char *wnd_name);
    explicit window_header_menu_t(const rectangle_t &enclosing, window_t &wnd, const char *wnd_name);

    void inline create            (const rectangle_t &enclosing);
private:
    void        create_close_btn  ();
    void        create_window_name();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    close_button_t close_btn;
    window_t      &window;
    label_t        window_name;

// friends
    friend window_header_menu_controller_t;
};

//--------------------------------------------------------------------------------------------------

inline void window_header_menu_t::create(const rectangle_t &enclosing_)
{
    enclosing = enclosing_;
    create_close_btn();
    create_window_name();
}

//--------------------------------------------------------------------------------------------------

inline void window_header_menu_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("window_header_menu", "");
}

#endif // WINDOW_HEADER_MENU_H
