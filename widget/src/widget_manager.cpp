#include <stdio.h>
#include "widget_manager.h"
#include "log.h"

//==================================================================================================

void widget_manager_t::on_widget_event_react(widget_t **widget_, const size_t widget_pos)
{
    widget_t &widget = **widget_;

    if (status == WIDGET_CLOSED)
        return;
    if (widget.status == WIDGET_CLOSED)
        list_erase(&widgets, widget_pos);
    else
        list_replace(&widgets, widget_, widget_pos, 0);
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_widgets_key_click_event(widget_t::on_key_click_event event, const KEY_TYPE &key)
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
            on_widget_event_react(cnt, ind);
            return true;
        }
        ++ind;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_widgets_mouse_click_event(widget_t::on_mouse_click_event event, const MOUSE_BUTTON_TYPE &btn)
{
    if (widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);
    size_t     ind   = 0;

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if ((cur.*event)(btn))
        {
            on_widget_event_react(cnt, ind);
            return true;
        }
        ++ind;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_widgets_mouse_move(const vec2d &off)
{
    if (widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);
    size_t     ind   = 0;

    for (widget_t **cnt = front; cnt != fict;
        cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if ((cur.on_mouse_move(off)))
        {
            on_widget_event_react(cnt, ind);
            return true;
        }
        ++ind;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::widgets_move(const vec2d &offset)
{
    if (widgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        cur.move(offset);
    }
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::widgets_recalc_region()
{
    if (widgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);

    for (widget_t **cnt_1 = front; cnt_1 != fict;
         cnt_1 = (widget_t **) list_next(cnt_1))
    {
        widget_t &cur_1 = **cnt_1;

        cur_1.visible.reset();
        cur_1.visible *= visible;

        for (widget_t **cnt_2 = front; cnt_2 != cnt_1;
             cnt_2 = (widget_t **) list_next(cnt_2))
        {
            widget_t &cur_2 = **cnt_2;
            cur_1.visible -= cur_2.visible;
        }

        cur_1.recalc_region();
        visible -= cur_1.visible.region;
    }
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::widgets_regions_dump() const
{
    if (widgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);

    LOG_TAB++;
    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;

        clipping_region_t::dump(&cur.visible);
        cur.dump_region();
    }
    LOG_TAB--;
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
