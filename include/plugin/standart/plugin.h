#ifndef PLUGIN_PLUGIN_H
#define PLUGIN_PLUGIN_H

#include <cinttypes>
#include "Interface.h"
#include "application.h"

//==================================================================================================

namespace plugin
{
    struct Plugin
    {
        uint64_t        id;
        const char   *name;
        InterfaceType type;

        virtual Interface *get_interface() = 0;
        virtual           ~Plugin       () {}
    };
}

extern "C" plugin::Plugin* getInstance(plugin::App *app);

#endif // PLUGIN_PLUGIN_H
