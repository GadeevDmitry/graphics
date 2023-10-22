#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include <assert.h>
#include "widget.h"
#include "data_structs/include/list.h"

//==================================================================================================

class widget_container_t: public widget_t
{
// member functions
public:
    explicit inline  widget_container_t(const rectangle_t &enclosing = rectangle_t());
             inline ~widget_container_t();

    bool register_subwidget       (widget_t *subwidget);
protected:
    void subwidgets_move          (const vec2d &offset);
    bool subwidgets_update_struct ();
    void subwidgets_recalc_areas  ();
    void subwidgets_dump          ()                                 const;
    void subwidgets_render        (render_texture_t &render_texture) const;

    bool on_subwidgets_key_press  (const key_context_t   &context, const KEY_TYPE          &key);
    bool on_subwidgets_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn);

// virtual
public:
    virtual void inline move            (const vec2d &offset) override;
    virtual void        dump            () const              override;
    virtual bool inline update_struct   ()                    override;
    virtual void inline recalc_areas    ()                    override;

    virtual bool inline on_key_press    (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_key_release  (const key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool inline on_mouse_press  (const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_move   (const mouse_context_t &context, const vec2d             &off) override;

// member data
protected:
    list subwidgets;

};

inline widget_container_t::widget_container_t(const rectangle_t &enclosing):
widget_t(enclosing)
{
    list_ctor(&subwidgets, sizeof(widget_t *));
}

//--------------------------------------------------------------------------------------------------

inline widget_container_t::~widget_container_t()
{
    list_dtor(&subwidgets);
}

//--------------------------------------------------------------------------------------------------

inline void widget_container_t::move(const vec2d &offset)
{
    visible.enclosing += offset;
    subwidgets_move(offset);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_container_t::update_struct()
{
    return subwidgets_update_struct();
}

//--------------------------------------------------------------------------------------------------

inline void widget_container_t::recalc_areas()
{
    subwidgets_recalc_areas();
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

#endif // WIDGET_MANAGER_H
