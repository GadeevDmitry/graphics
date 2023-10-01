#include <stdio.h>
#include "window.h"

//==================================================================================================

bool window_t::on_key_event(key_event event, const KEY_TYPE key)
{
    widget_t **front = (widget_t **) list_front(&sub_widgets);
    widget_t **back  = (widget_t **) list_back (&sub_widgets);

    for (widget_t **sub_widget = front; sub_widget <= back;
         sub_widget = (widget_t **) list_next(sub_widget))
    {
        if (((*sub_widget)->*event)(key))
        {
            list_replace(&sub_widgets, sub_widget, 0);
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_event(mouse_event event, const vec2d &pos, const MOUSE_BUTTON_TYPE btn)
{
    if (!is_mouse_inside(pos)) return false;

    widget_t **front = (widget_t **) list_front(&sub_widgets);
    widget_t **back  = (widget_t **) list_back (&sub_widgets);

    for (widget_t **sub_widget = front; sub_widget <= back;
         sub_widget = (widget_t **) list_next(sub_widget))
    {
        if (((*sub_widget)->*event)(pos, btn))
        {
            list_replace(&sub_widgets, sub_widget, 0);
            return true;
        }
    }
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void texture_window_t::render(render_texture_t *wnd) const
{
    wnd->draw_texture(texture, area.ld_corner, area.get_size());

    widget_t **front = (widget_t **) list_front(&sub_widgets);
    widget_t **back  = (widget_t **) list_back (&sub_widgets);

    for (widget_t **sub_widget = back; sub_widget >= front;
         sub_widget = (widget_t **) list_prev(sub_widget))
    {
        (*sub_widget)->render(wnd);
    }
}
