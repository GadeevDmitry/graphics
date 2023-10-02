#include <stdio.h>
#include "window.h"
#include "log.h"

//==================================================================================================

bool window_t::on_key_event(key_event event, const KEY_TYPE key)
{
    if (sub_widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&sub_widgets);
    widget_t **fict  = (widget_t **) list_fict (&sub_widgets);
    size_t     ind   = 0;

    for (widget_t **sub_widget = front; sub_widget != fict;
         sub_widget = (widget_t **) list_next(sub_widget))
    {
        if (((*sub_widget)->*event)(key))
        {
            list_replace(&sub_widgets, sub_widget, ind, 0);
            return true;
        }
        ind++;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_event(mouse_event event, const vec2d &pos, const MOUSE_BUTTON_TYPE btn)
{
    if (!is_mouse_inside(pos)) return false;
    if (sub_widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&sub_widgets);
    widget_t **fict  = (widget_t **) list_fict (&sub_widgets);
    size_t     ind   = 0;

    for (widget_t **sub_widget = front; sub_widget != fict;
         sub_widget = (widget_t **) list_next(sub_widget))
    {
        if (((*sub_widget)->*event)(pos, btn))
        {
            list_replace(&sub_widgets, sub_widget, ind, 0);
            return true;
        }
        ind++;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------

void window_t::render_sub_widgets(render_texture_t &wnd) const
{
    widget_t **back = (widget_t **) list_back(&sub_widgets);
    widget_t **fict = (widget_t **) list_fict(&sub_widgets);

    for (widget_t **sub_widget = back; sub_widget != fict;
         sub_widget = (widget_t **) list_prev(sub_widget))
    {
        (*sub_widget)->render(wnd);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void texture_window_t::render(render_texture_t &wnd) const
{
    wnd.draw_texture(texture, area.ld_corner, area.get_size());
    render_sub_widgets(wnd);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void color_window_t::render(render_texture_t &wnd) const
{
    wnd.draw_filled_rectangle(area, color);
    render_sub_widgets(wnd);
}
