#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include "list.h"
#include "widget.h"

//==================================================================================================

class widget_manager_t: public widget_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    bool on_widgets_key_click_event  (on_key_click_event   event, const KEY_TYPE          &key);
    bool on_widgets_mouse_click_event(on_mouse_click_event event, const MOUSE_BUTTON_TYPE &btn);

    void on_widget_event_react       (widget_t **widget_, const size_t widget_pos);

protected:
    list widgets;

    inline          widget_manager_t(void (*delete_widget) (void *el));
    inline explicit widget_manager_t(void (*delete_widget) (void *el), const rectangle_t &region_);
    inline         ~widget_manager_t();

    inline bool register_widget(widget_t *widget);

    void widgets_move         (const vec2d &offset);
    void widgets_recalc_region();
    void widgets_render       (render_texture_t &render_texture) const;

    inline bool on_widgets_key_press    (const KEY_TYPE          &key);
    inline bool on_widgets_key_release  (const KEY_TYPE          &key);
    inline bool on_widgets_mouse_press  (const MOUSE_BUTTON_TYPE &btn);
    inline bool on_widgets_mouse_release(const MOUSE_BUTTON_TYPE &btn);
           bool on_widgets_mouse_move   (const vec2d             &off);

public:
    void widgets_regions_dump () const;

    virtual inline void move         (const vec2d &off)            override;
    virtual inline void recalc_region()                            override;
    virtual inline void render       (render_texture_t &wnd) const override;

    virtual inline bool on_key_press    (const KEY_TYPE          &key) override;
    virtual inline bool on_key_release  (const KEY_TYPE          &key) override;
    virtual inline bool on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override;
    virtual inline bool on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    virtual inline bool on_mouse_move   (const vec2d             &off) override;
};

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::widget_manager_t(void (*delete_widget) (void *el))
{
    list_ctor(&widgets, sizeof(widget_t *), delete_widget);
}

//--------------------------------------------------------------------------------------------------

inline widget_manager_t::widget_manager_t(void (*delete_widget) (void *el), const rectangle_t &region_):
widget_t(region_)
{
    list_ctor(&widgets, sizeof(widget_t *), delete_widget);
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
    return on_widgets_key_click_event(&widget_t::on_key_press, key);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_key_release(const KEY_TYPE &key)
{
    return on_widgets_key_click_event(&widget_t::on_key_release, key);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    return on_widgets_mouse_click_event(&widget_t::on_mouse_press, btn);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_widgets_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    return on_widgets_mouse_click_event(&widget_t::on_mouse_release, btn);
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::move(const vec2d &off)
{
    widgets_move(off);
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::recalc_region()
{
    widgets_recalc_region();
}

//--------------------------------------------------------------------------------------------------

inline void widget_manager_t::render(render_texture_t &wnd) const
{
    widgets_render(wnd);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_key_press(const KEY_TYPE &key)
{
    return on_widgets_key_press(key);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_key_release(const KEY_TYPE &key)
{
    return on_widgets_key_release(key);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    return on_widgets_mouse_press(btn);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    return on_widgets_mouse_release(btn);
}

//--------------------------------------------------------------------------------------------------

inline bool widget_manager_t::on_mouse_move(const vec2d &off)
{
    return on_widgets_mouse_move(off);
}

#endif // WIDGET_MANAGER_H
