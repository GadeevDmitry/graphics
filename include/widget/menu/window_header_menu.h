#ifndef WINDOW_HEADER_MENU_H
#define WINDOW_HEADER_MENU_H

#include "widget/menu.h"
#include "widget/label.h"
#include "widget/button/close_button.h"

//==================================================================================================

class window_t;

class window_header_menu_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline window_header_menu_controller_t(window_t &to_move);

// virtual
public:
    virtual bool on_mouse_move(widget_t *handle, const eventable::mouse_context_t &context, const vec2d &off) override;

// member data
private:
    window_t &to_move;
};

//--------------------------------------------------------------------------------------------------

inline window_header_menu_controller_t::window_header_menu_controller_t(window_t &to_move_):
to_move(to_move_)
{}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class window_header_menu_t: public menu_t
{
// member functions
public:
    explicit window_header_menu_t(window_header_menu_controller_t &controller,                               window_t &wnd, const char *wnd_name);
    explicit window_header_menu_t(window_header_menu_controller_t &controller, const rectangle_t &enclosing, window_t &wnd, const char *wnd_name);

    void inline create            (const rectangle_t &enclosing);
private:
    void        create_close_btn  ();
    void        create_window_name();

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
private:
    close_button_controller_t close_btn_controller;
    close_button_t            close_btn;
    label_t                   window_name;
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
