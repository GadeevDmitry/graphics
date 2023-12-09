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
    // member functions
    public:
        explicit inline Plugin(uint64_t id, const char *name, InterfaceType type);

    // virtual
    public:
        virtual Interface *get_interface() = 0;
        virtual           ~Plugin       () {}

    // member data
    public:
        uint64_t        id;
        const char   *name;
        InterfaceType type;
    };

    //--------------------------------------------------------------------------------------------------

    inline Plugin::Plugin(uint64_t id_, const char *name_, InterfaceType type_):
    id  (id_),
    name(name_),
    type(type_)
    {}
}

extern "C" plugin::Plugin* getInstance(plugin::App *app);

#endif // PLUGIN_PLUGIN_H
