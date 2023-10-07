#include <stdio.h>
#include "widget_manager.h"

//==================================================================================================

void widget_manager_t::on_widget_event_reaction(widget_t **widget_, const size_t widget_pos)
{
    widget_t &widget = **widget_;

    if (status == WIDGET_CLOSED)
        return;
    if (widget.get_status() == WIDGET_CLOSED)
        list_erase(&widgets, widget_pos);
    else
        list_replace(&widgets, widget_, widget_pos, 0);

    return;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_widgets_key_event
    (widget_t::on_key_event event, const KEY_TYPE &key)
{
    if (widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);
    size_t     ind   = 0;

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if ((cur.*event)(key))
        {
            on_widget_event_reaction(cnt, ind);
            return true;
        }

        ++ind;
        continue;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_widgets_mouse_event
    (widget_t::on_mouse_event event, const mouse_context_t &context)
{
    if (widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);
    size_t     ind   = 0;

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if ((cur.*event)(context))
        {
            on_widget_event_reaction(cnt, ind);
            return true;
        }

        ++ind;
        continue;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::widgets_render(render_texture_t &render_texture) const
{
    if (widgets.size == 0) return;

    widget_t **back = (widget_t **) list_back(&widgets);
    widget_t **fict = (widget_t **) list_fict(&widgets);

    for (widget_t **cnt = back; cnt != fict;
         cnt = (widget_t **) list_prev(cnt))
    {
        widget_t &cur = **cnt;
        cur.render(render_texture);
    }
}
