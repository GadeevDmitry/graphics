#ifndef EXTERNAL_MENU_BUTTON_H
#define EXTERNAL_MENU_BUTTON_H

#include "widget/menu.h"
#include "widget/button/label_button.h"

//==================================================================================================

class external_menu_button_controller_t: public widget_controller_t
{
// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
};

//--------------------------------------------------------------------------------------------------

inline bool external_menu_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class external_menu_button_t: public label_button_t
{
// static
public:
    static external_menu_button_controller_t external_menu_button_controller;

// member functions
public:
    explicit external_menu_button_t(menu_t &external_menu,                               const char *btn_name);
    explicit external_menu_button_t(menu_t &external_menu, const rectangle_t &enclosing, const char *btn_name);

// virtual
public:
    virtual void inline move          (const vec2d &offset)         override;
    virtual void        dump          ()                      const override;
    virtual void inline graphic_dump  (render_texture_t &wnd) const override;
    virtual bool        update_struct ()                            override;
    virtual void        recalc_regions()                            override;

    virtual bool        on_key_press  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool        on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

    virtual void inline render        (render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    bool    is_menu_hidden;
    menu_t &external_menu;
};

//--------------------------------------------------------------------------------------------------

inline void external_menu_button_t::move(const vec2d &offset)
{
    enclosing += offset;
    external_menu.move(offset);
}

//--------------------------------------------------------------------------------------------------

inline void external_menu_button_t::graphic_dump(render_texture_t &wnd) const
{
    wnd.draw_region(              own_visible);
    wnd.draw_region(external_menu.own_visible);
}

//--------------------------------------------------------------------------------------------------

inline void external_menu_button_t::render(render_texture_t &wnd)
{
    label_button_t::render(wnd);
    if (!is_menu_hidden) external_menu.render(wnd);
}

//--------------------------------------------------------------------------------------------------

inline void external_menu_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("external_menu_button_t", "");
}

#endif // EXTERNAL_MENU_BUTTON_H
