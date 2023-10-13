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

    LOG_TAB_SERVICE_MESSAGE("WIDGET_MANAGER_T::ON_WIDGETS_MOUSE_CLICK_EVENT", "\n");
    LOG_TAB++;
    LOG_TAB_MESSAGE("size  = %lu\n"
                    "front = %p\n", widgets.size, *front);


    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if ((cur.*event)(btn))
        {
            on_widget_event_react(cnt, ind);
            LOG_TAB--;
            return true;
        }
        ++ind;
    }

    LOG_TAB--;
    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_widgets_mouse_move(const vec2d &off)
{
    if (widgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&widgets);
    widget_t **fict  = (widget_t **) list_fict (&widgets);
    size_t     ind   = 0;

    LOG_TAB_SERVICE_MESSAGE("WIDGET_MANAGER_T::ON_WIDGETS_MOUSE_MOVE", "\n");
    LOG_TAB++;
    LOG_TAB_MESSAGE("size = %lu\n", widgets.size);

    for (widget_t **cnt = front; cnt != fict;
        cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if ((cur.on_mouse_move(off)))
        {
            on_widget_event_react(cnt, ind);
            LOG_TAB--;
            return true;
        }
        ++ind;
    }

    LOG_TAB--;
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
