#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include "list.h"
#include "widget.h"
#include <assert.h>

//==================================================================================================

class widget_manager_t: public widget_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    list subwidgets;
    bool register_subwidget(widget_t *subwidget);

    void subwidgets_move         (const vec2d &offset);
    bool subwidgets_update_struct();
    void subwidgets_recalc_region();
    void subwidgets_dump_region  ()                                 const;
    void subwidgets_render       (render_texture_t &render_texture) const;

    bool on_subwidgets_key_press    (const KEY_TYPE          &key);
    bool on_subwidgets_mouse_press  (const MOUSE_BUTTON_TYPE &btn);

    void virtual inline move         (const vec2d &offset) override;
    bool virtual inline update_struct()                    override;
    void virtual inline recalc_region()                    override;

    bool virtual inline on_key_press    (const KEY_TYPE          &key) override;
    bool virtual inline on_key_release  (const KEY_TYPE          &key) override;
    bool virtual inline on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    bool virtual inline on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    bool virtual inline on_mouse_move   (const vec2d             &off) override;

public:
             inline  widget_manager_t(void (*delete_widget) (void *el));
    explicit inline  widget_manager_t(void (*delete_widget) (void *el), const rectangle_t &region_);
             inline ~widget_manager_t();

    void virtual inline dump_region()                const override;
    void virtual inline render     (render_texture_t &wnd) override;
};

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::widget_manager_t(void (*delete_widget) (void *el))
{
    list_ctor(&subwidgets, sizeof(widget_t *), delete_widget);
}

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::widget_manager_t(void (*delete_widget) (void *el), const rectangle_t &region_):
widget_t(region_)
{
    list_ctor(&subwidgets, sizeof(widget_t *), delete_widget);
}

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::~widget_manager_t()
{
    list_dtor(&subwidgets);
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::move(const vec2d &offset)
{
    visible.region += offset;
    subwidgets_move(offset);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::update_struct()
{
    return subwidgets_update_struct();
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::recalc_region()
{
    subwidgets_recalc_region();
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::dump_region() const
{
    return subwidgets_dump_region();
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::render(render_texture_t &wnd)
{
    subwidgets_render(wnd);
}

//--------------------------------------------------------------------------------------------------

/**
*   По умолчанию менеджер служит посредником между родительским виджетом и подвиджетами.
*   Это означает, что он не может быть активен и в случае нажатия должен вызываться только тогда,
*   когда активных виджетов нет, для передачи нажатия в подвиджеты.
*
*   Для производных классов функция должна быть переопределена, если утверждение выше нарушено.
*/
inline bool widget_manager_t::on_key_press(const KEY_TYPE &key)
{
    assert(active == nullptr);
    return on_subwidgets_key_press(key);
}

//--------------------------------------------------------------------------------------------------

/**
*   По соглашению в случае отпускания должен вызываться обработчик активного виджета.
*   Если активного виджета нет, отпускание игнорируется. Так как по умолчанию менеджер
*   не может быть активен, то вызываться в случае отпускания не должен.
*
*   Для производных классов функция должна быть переопределена, если утверждение выше нарушено.
*/
inline bool widget_manager_t::on_key_release(const KEY_TYPE &key)
{
    assert("called key release from default widget manager\n");
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

/**
*   Аналогично widget_manager_t::on_key_press(KEY_TYPE &key).
*/
inline bool widget_manager_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    assert(active == nullptr);
    return on_subwidgets_mouse_press(btn);
}

//--------------------------------------------------------------------------------------------------

/**
*   Аналогично widget_manager_t::on_key_release(KEY_TYPE &key).
*/
inline bool widget_manager_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    assert("called mouse release from default widget manager\n");
    (void) btn;
    return false;
}

//--------------------------------------------------------------------------------------------------

/**
*   По соглашению в случае движения мыши должен вызываться обработчик активного виджета.
*   Если активного виджета нет, движение игнорируется.
*
*   Аналогично widget_manager_t::on_key_release(KEY_TYPE &key).
*/
inline bool widget_manager_t::on_mouse_move(const vec2d &off)
{
    assert("called mouse move from default widget manager\n");
    (void) off;
    return false;
}

#endif // WIDGET_MANAGER_H
