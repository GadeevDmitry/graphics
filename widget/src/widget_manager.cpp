#include <stdio.h>
#include "widget_manager.h"
#include "log.h"

//==================================================================================================

bool widget_manager_t::register_subwidget(widget_t *subwidget)
{
    if (list_push_front(&subwidgets, &subwidget))
    {
        subwidget->ancestor = this;
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_subwidgets_key_press(const KEY_TYPE &key)
{
    if (subwidgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if (cur.on_key_press(key)) return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::on_subwidgets_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    if (subwidgets.size == 0) return false;

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        if (cur.on_mouse_press(btn)) return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::subwidgets_move(const vec2d &offset)
{
    if (subwidgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;
        cur.move(offset);
    }
}

//--------------------------------------------------------------------------------------------------

void widget_manager_t::subwidgets_recalc_region()
{
    if (subwidgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);

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

void widget_manager_t::subwidgets_dump_region() const
{
    if (subwidgets.size == 0) return;

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);

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

void widget_manager_t::subwidgets_render(render_texture_t &render_texture) const
{
    if (subwidgets.size == 0) return;

    widget_t **back = (widget_t **) list_back(&subwidgets);
    widget_t **fict = (widget_t **) list_fict(&subwidgets);

    for (widget_t **cnt = back; cnt != fict;
         cnt = (widget_t **) list_prev(cnt))
    {
        widget_t &cur = **cnt;
        cur.render(render_texture);
    }
}

//--------------------------------------------------------------------------------------------------

bool widget_manager_t::subwidgets_update_struct()
{
    if (status == WIDGET_CLOSED) return true;
    if (subwidgets.size == 0)    return false;

    widget_t **front = (widget_t **) list_front(&subwidgets);
    widget_t **fict  = (widget_t **) list_fict (&subwidgets);
    size_t     ind   = 0;

    for (widget_t **cnt = front; cnt != fict;
         cnt = (widget_t **) list_next(cnt))
    {
        widget_t &cur = **cnt;

        switch (cur.status)
        {
            case WIDGET_OPENED : break;

            case WIDGET_CLOSED : list_erase(&subwidgets, ind);
                                 return true;

            case WIDGET_UPDATED: list_replace(&subwidgets, cnt, ind, 0);
                                 cur.status = WIDGET_OPENED;
                                 cur.update_struct();
                                 return true;
            default: break;
        }

        ++ind;
    }

    return false;
}
