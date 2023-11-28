#include <stdio.h>
#include "host/HostWidgetI.h"

//==================================================================================================

namespace host
{
    void HostWidgetI::register_subwidget(WidgetI *object)
    {
        root.register_subwidget(widget_proxy_t(object));
    }

    //--------------------------------------------------------------------------------------------------

    void HostWidgetI::unregister_subwidget(WidgetI *object)
    {
        widget_proxy_t *child = (widget_proxy_t *) list_front(&root.subwidgets);
        widget_proxy_t *fict  = (widget_proxy_t *) list_fict (&root.subwidgets);

        for (size_t cnt = 0; child != fict; ++cnt)
        {
            if (!child->is_internal && object == child->external)
            {
                list_erase(&root.subwidgets, cnt);
                return;
            }

            child = (widget_proxy_t *) list_next(child);
        }

        LOG_ERROR("attempt to delete an unregistered object\n");
    }
}
