#ifndef PLUGIN_WIDGET_H
#define PLUGIN_WIDGET_H

#include "Event.h"
#include "Render.h"

//==================================================================================================

namespace plugin
{
    struct WidgetI: public EventProcessableI
    {
        virtual void       register_subwidget(WidgetI* object) = 0;
        virtual void     unregister_subwidget(WidgetI* object) = 0;

        virtual vec2d    get_size            ()                = 0;
        virtual vec2d    set_size            (vec2d size)      = 0;

        virtual vec2d    get_pos             ()                = 0;
        virtual void     set_pos             (vec2d pos)       = 0;

        virtual bool     isExtern            ()                = 0;

        virtual void     set_parent          (WidgetI *root)   = 0;
        virtual WidgetI *get_parent          ()                = 0;

        virtual void     move                (vec2d shift)     = 0;

        virtual bool     get_available       ()                = 0;
        virtual void     set_available       (bool)            = 0;

        virtual void     render              (RenderTargetI* ) = 0;
        virtual void     recalcRegion        ()                = 0;

        virtual         ~WidgetI             ()                = 0;
    };
}

#endif // PLUGIN_WIDGET_H
