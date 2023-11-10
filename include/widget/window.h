#ifndef WINDOW_H
#define WINDOW_H

#include "menu.h"
#include "menu/window_header_menu.h"

//==================================================================================================

class window_controller_t: public widget_controller_t
{
// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
};

//--------------------------------------------------------------------------------------------------

inline bool window_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class window_t: public menu_t
{
// static
public:
    static const color_t Light_theme;
    static const color_t Dark_theme;
    static const color_t Blue_theme;
    static const color_t Red_theme;

    static const double header_menu_height;

// member functions
public:
    explicit window_t(widget_controller_t &controller,                               const color_t &color = Red_theme);
    explicit window_t(widget_controller_t &controller, const rectangle_t &enclosing, const color_t &color = Red_theme);

    bool inline register_subwindow(window_t *window);
    void inline set_window_name   (const font_t *font, const char *string);
    void inline create            (const rectangle_t &enclosing);
private:
    void        create_header_menu();

// member data
private:
    window_header_menu_controller_t header_menu_controller;
    window_header_menu_t            header_menu;
};

//--------------------------------------------------------------------------------------------------

inline bool window_t::register_subwindow(window_t *window)
{
    return register_subwidget(window);
}

//--------------------------------------------------------------------------------------------------

inline void window_t::set_window_name(const font_t *font, const char *string)
{
    return header_menu.set_window_name(font, string);
}

//--------------------------------------------------------------------------------------------------

inline void window_t::create(const rectangle_t &enclosing)
{
    visible.enclosing = enclosing;
    create_header_menu();
}

#endif // WINDOW_H
