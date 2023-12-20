#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include <assert.h>
#include "widget_proxy.h"
#include "data_structs/include/list.h"

//==================================================================================================

namespace host
{
    class HostWidgetI;
}

class widget_container_t: public widget_t
{
// member functions
public:
             inline  widget_container_t(                              const bool to_delete = false);
    explicit inline  widget_container_t(const rectangle_t &enclosing, const bool to_delete = false);
             inline ~widget_container_t();

    bool   register_subwidget     (const widget_proxy_t &subwidget);
    bool unregister_subwidget     (const widget_proxy_t &subwidget);
protected:
    void subwidgets_move          (const vec2d &offset);
    void subwidgets_dump          () const;
    void subwidgets_graphic_dump  (render_texture_t &wnd) const;
    bool subwidgets_update_struct ();
    void subwidgets_recalc_regions();

    bool on_subwidgets_key_press  (const key_context_t   &context, const KEY_TYPE          &key);
    bool on_subwidgets_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn);

    void subwidgets_render        (render_texture_t &render_texture) const;

// virtual
public:
    virtual void inline move            (const vec2d &offset)         override;
    virtual void        dump            ()                      const override;
    virtual void inline graphic_dump    (render_texture_t &wnd) const override;
    virtual bool inline update_struct   ()                            override;
    virtual void inline recalc_regions  ()                            override;

    virtual bool inline on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;
protected:
    virtual void inline dump_class_name () const override;

// member data
protected:
    list subwidgets;

// friends
    friend host::HostWidgetI;
};

//--------------------------------------------------------------------------------------------------

inline widget_container_t::widget_container_t(const bool to_delete):
widget_t(rectangle_t())
{
    if (to_delete) list_ctor(&subwidgets, sizeof(widget_proxy_t), widget_proxy_t::widget_proxy_dtor_internal);
    else           list_ctor(&subwidgets, sizeof(widget_proxy_t), widget_proxy_t::widget_proxy_dtor);
}

//--------------------------------------------------------------------------------------------------

inline widget_container_t::widget_container_t(const rectangle_t &enclosing_, const bool to_delete):
widget_t(enclosing_)
{
    if (to_delete) list_ctor(&subwidgets, sizeof(widget_proxy_t), widget_proxy_t::widget_proxy_dtor_internal);
    else           list_ctor(&subwidgets, sizeof(widget_proxy_t), widget_proxy_t::widget_proxy_dtor);
}

//--------------------------------------------------------------------------------------------------

inline widget_container_t::~widget_container_t()
{
    list_dtor(&subwidgets);
}

//--------------------------------------------------------------------------------------------------

inline void widget_container_t::move(const vec2d &offset)
{
    enclosing += offset;
    subwidgets_move(offset);
}

//--------------------------------------------------------------------------------------------------

inline void widget_container_t::graphic_dump(render_texture_t &wnd) const
{
    wnd.draw_region(own_visible);
    subwidgets_graphic_dump(wnd);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_container_t::update_struct()
{
    return subwidgets_update_struct();
}

//--------------------------------------------------------------------------------------------------

inline void widget_container_t::recalc_regions()
{
    subwidgets_recalc_regions();
}

//--------------------------------------------------------------------------------------------------

/**
*   По умолчанию контейнер служит посредником между родительским виджетом и подвиджетами.
*   Это означает, что контейнер при нажатии должен вызываться только для передачи нажатия в подвиджеты.
*
*   Для производных классов функция должна быть переопределена, если утверждение выше нарушено.
*/
inline bool widget_container_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    return on_subwidgets_key_press(context, key);
}

//--------------------------------------------------------------------------------------------------

/**
*   По соглашению при отпускании должен вызываться обработчик активного виджета.
*   Если активного виджета нет (active == nullptr), отпускание игнорируется. По умолчанию контейнер
*   не может быть активен, поэтому вызываться в случае отпускания не должен.
*
*   Для производных классов функция должна быть переопределена, если утверждение выше нарушено.
*/
inline bool widget_container_t::on_key_release(const key_context_t &context, const KEY_TYPE &key)
{
    assert("called \"on_key_release\" of default widget manager\n");
    (void) context;
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

/**
*   Аналогично widget_container_t::on_key_press(KEY_TYPE &key).
*/
inline bool widget_container_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    return on_subwidgets_mouse_press(context, btn);
}

//--------------------------------------------------------------------------------------------------

/**
*   Аналогично widget_container_t::on_key_release(KEY_TYPE &key).
*/
inline bool widget_container_t::on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    assert("called mouse release from default widget manager\n");
    (void) context;
    (void) btn;
    return false;
}

//--------------------------------------------------------------------------------------------------

/**
*   По соглашению в случае движения мыши должен вызываться обработчик активного виджета.
*   Если активного виджета нет, движение игнорируется.
*
*   Аналогично widget_container_t::on_key_release(KEY_TYPE &key).
*/
inline bool widget_container_t::on_mouse_move(const mouse_context_t &context, const vec2d &off)
{
    assert("called mouse move from default widget manager\n");
    (void) context;
    (void) off;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline void widget_container_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("widget_container_t", "");
}

#endif // WIDGET_MANAGER_H
