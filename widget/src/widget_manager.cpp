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

void widget_manager_t::widgets_recalc_region(const vec2d &offset)
{
    if (widgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);

    for (widget_t **cnt_1 = front; cnt_1 != fict;
         cnt_1 = (widget_t **) list_next(cnt_1))
    {
        widget_t          &cur_1     = **cnt_1;
        clipping_region_t &cur_1_reg = cur_1.get_clipping_region();

        cur_1_reg.set_region(cur_1_reg.get_region() + offset);
        cur_1_reg.reset();
        cur_1_reg *= visible;

        for (widget_t **cnt_2 = front; cnt_2 != cnt_1;
             cnt_2 = (widget_t **) list_next(cnt_2))
        {
            widget_t          &cur_2     = **cnt_2;
            clipping_region_t &cur_2_reg = cur_2.get_clipping_region();

            cur_1_reg -= cur_2_reg.get_region();
        }

        cur_1.recalc_region(cur_1_reg.get_region().ld_corner);
    }
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::recalc_region(const vec2d &offset)
{
    visible.set_region(visible.get_region() + offset);
    visible.reset();

    widgets_recalc_region(offset);

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        renderable        &cur     = **cnt;
        clipping_region_t &cur_reg = cur.get_clipping_region();

        visible -= cur_reg.get_region();
    }
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::widgets_render(render_texture_t &render_texture, const vec2d &offset) const
{
    if (widgets.size == 0) return;

    widget_t **back = (widget_t **) list_back(&widgets);
    widget_t **fict = (widget_t **) list_fict(&widgets);

    for (widget_t **cnt = back; cnt != fict;
         cnt = (widget_t **) list_prev(cnt))
    {
        widget_t &cur = **cnt;
        cur.render(render_texture, offset);
    }
}
