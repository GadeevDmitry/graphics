#ifndef WINDOW_HEADER_MENU_H
#define WINDOW_HEADER_MENU_H

#include "widget/menu.h"
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
    explicit window_header_menu_t(window_header_menu_controller_t &controller, widget_t &to_close,                               const color_t &color = color_t());
    explicit window_header_menu_t(window_header_menu_controller_t &controller, widget_t &to_close, const rectangle_t &enclosing, const color_t &color = color_t());

    void inline create(const rectangle_t &enclosing);
private:
    void        create_close_btn();

// member data
private:
    close_button_controller_t close_btn_controller;
    close_button_t            close_btn;
};

//--------------------------------------------------------------------------------------------------

inline void window_header_menu_t::create(const rectangle_t &enclosing)
{
    visible.enclosing = enclosing;
    create_close_btn();
}

#endif // WINDOW_HEADER_MENU_H
