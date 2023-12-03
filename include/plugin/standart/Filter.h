#ifndef PLUGIN_FILTER_H
#define PLUGIN_FILTER_H

#include "Render.h"
#include "Interface.h"

//==================================================================================================

namespace plugin
{
    struct FilterI: public Interface
    {
        virtual void apply(RenderTargetI *perm) = 0;
    };

    struct FilterManagerI
    {
        virtual void set_render_target(RenderTargetI *target) = 0;
        virtual void set_filter       (FilterI       *filter) = 0;
        virtual void apply_filter     ()                      = 0;
    };

};

#endif // PLUGIN_FILTER_H
