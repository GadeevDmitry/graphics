#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include "list.h"
#include "widget.h"

//==================================================================================================

class widget_manager_t: public widget_t
{
private:
    bool on_widgets_key_event  (on_key_event   event, const KEY_TYPE &key);
    bool on_widgets_mouse_event(on_mouse_event event, const mouse_context_t &context);

    void on_widget_event_reaction(widget_t **widget_, const size_t widget_pos);

protected:
    list widgets;

    inline          widget_manager_t();
    inline explicit widget_manager_t(const rectangle_t &region_);
    inline         ~widget_manager_t();

    inline bool register_widget(widget_t *widget);

    inline bool on_widgets_key_press  (const KEY_TYPE &key);
    inline bool on_widgets_key_release(const KEY_TYPE &key);

    inline bool on_widgets_mouse_press  (const mouse_context_t &context);
    inline bool on_widgets_mouse_release(const mouse_context_t &context);

    void widgets_render(render_texture_t &render_texture) const;

};

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::widget_manager_t()
{
    list_ctor(&widgets, sizeof(widget_t *), widget_delete);
}

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::widget_manager_t(const rectangle_t &region_):
widget_t(region_)
{
    list_ctor(&widgets, sizeof(widget_t *), widget_delete);
}

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::~widget_manager_t()
{
    list_dtor(&widgets);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::register_widget(widget_t *widget)
{
    return list_push_front(&widgets, &widget);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_key_press(const KEY_TYPE &key)
{
    return on_widgets_key_event(&widget_t::on_key_press, key);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_key_release(const KEY_TYPE &key)
{
    return on_widgets_key_event(&widget_t::on_key_release, key);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_mouse_press(const mouse_context_t &context)
{
    return on_widgets_mouse_event(&widget_t::on_mouse_press, context);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_mouse_release(const mouse_context_t &context)
{
    return on_widgets_mouse_event(&widget_t::on_mouse_release, context);
}

#endif // WIDGET_MANAGER_H
