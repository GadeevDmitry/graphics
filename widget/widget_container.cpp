#include <stdio.h>
#include "widget_container.h"
#include "data_structs/include/log.h"

//==================================================================================================

bool widget_container_t::register_subwidget(const widget_proxy_t &subwidget)
{
    if (list_push_front(&subwidgets, &subwidget))
    {
        LOG_ASSERT(subwidget.is_internal);
        subwidget.internal->ancestor = this;

        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_container_t::unregister_subwidget(const widget_proxy_t &subwidget)
{
    return list_erase(&subwidgets, &subwidget);
}

//--------------------------------------------------------------------------------------------------

void widget_container_t::subwidgets_move(const vec2d &offset)
{
    if (subwidgets.size == 0) return;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        cnt->move(offset);
    }
}

//--------------------------------------------------------------------------------------------------

void widget_container_t::subwidgets_dump() const
{
    if (subwidgets.size == 0) return;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    LOG_TAB++;
    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        if (cnt->is_internal)
            cnt->internal->dump();
    }
    LOG_TAB--;
}

//--------------------------------------------------------------------------------------------------

void widget_container_t::subwidgets_graphic_dump(render_texture_t &wnd) const
{
    if (subwidgets.size == 0) return;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        if (cnt->is_internal)
            cnt->internal->graphic_dump(wnd);
    }
};

//--------------------------------------------------------------------------------------------------

bool widget_container_t::subwidgets_update_struct()
{
    if (status == WIDGET_CLOSED) return true;
    if (subwidgets.size == 0)    return false;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);
    size_t          ind   = 0;

    bool is_true = false;

    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        switch (cnt->get_status())
        {
            case WIDGET_OPENED   : break;

            case WIDGET_CLOSED   : list_erase(&subwidgets, ind);
                                   is_true = true;
                                   break;

            case WIDGET_ACTIVATED: LOG_ASSERT(cnt->is_internal);

                                   list_replace(&subwidgets, cnt, ind, 0);
                                   cnt->internal->status = WIDGET_OPENED;
                                   cnt->internal->update_struct();
                                   is_true = true;
                                   break;
            default: break;
        }
        ++ind;
    }

    return is_true;
}

//--------------------------------------------------------------------------------------------------

void widget_container_t::subwidgets_recalc_regions()
{
    if (subwidgets.size == 0) return;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (widget_proxy_t *cnt_1 = front; cnt_1 != fict;
         cnt_1 = (widget_proxy_t *) list_next(cnt_1))
    {
        if (!cnt_1->is_internal)
        {
            cnt_1->external->recalcRegion();
            continue;
        }

        cnt_1->internal->reset_regions();
        cnt_1->internal->own_visible *= own_visible;

        for (widget_proxy_t *cnt_2 = front; cnt_2 != cnt_1;
             cnt_2 = (widget_proxy_t *) list_next(cnt_2))
        {
            if (!cnt_2->is_internal)
                continue;

            cnt_1->internal->own_visible -= cnt_2->internal->sub_enclosing;
        }

        cnt_1->internal->recalc_regions();
        own_visible -= cnt_1->internal->sub_enclosing;
    }
}

//--------------------------------------------------------------------------------------------------

bool widget_container_t::on_subwidgets_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    if (subwidgets.size == 0) return false;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        if (cnt->on_key_press(context, key)) return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool widget_container_t::on_subwidgets_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    if (subwidgets.size == 0) return false;

    widget_proxy_t *front = (widget_proxy_t *) list_front(&subwidgets);
    widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&subwidgets);

    for (widget_proxy_t *cnt = front; cnt != fict;
         cnt = (widget_proxy_t *) list_next(cnt))
    {
        if (cnt->on_mouse_press(context, btn)) return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

void widget_container_t::subwidgets_render(render_texture_t &render_texture) const
{
    if (subwidgets.size == 0) return;

    widget_proxy_t *back = (widget_proxy_t *) list_back(&subwidgets);
    widget_proxy_t *fict = (widget_proxy_t *) list_fict(&subwidgets);

    for (widget_proxy_t *cnt = back; cnt != fict;
         cnt = (widget_proxy_t *) list_prev(cnt))
    {
        cnt->render(render_texture);
    }
}

//--------------------------------------------------------------------------------------------------

void widget_container_t::dump() const
{
    dump_class_name();
    LOG_SERVICE_MESSAGE("(address: %p)\n{", "\n", this);
    LOG_TAB++;

    USUAL_FIELD_DUMP("status  ", "%d", status);
    USUAL_FIELD_DUMP("ancestor", "%p", ancestor);

    renderable::dump();

    LOG_TAB_SERVICE_MESSAGE("subwidgets:\n{", "\n");
    LOG_TAB++;
    subwidgets_dump();
    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n\n");
}
