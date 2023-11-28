#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <cinttypes>

//==================================================================================================

namespace plugin
{
    template<class T>
    struct Array
    {
        uint64_t size;
        T       *data;
    };

    enum class InterfaceType
    {
        Tool,
        Filter
    };

    struct Interface
    {
        virtual Array<const char *> get_param_names()                     = 0;
        virtual Array<double>       get_params     ()                     = 0;
        virtual void                set_params     (Array<double> params) = 0;
    };
}

#endif // PLUGIN_INTERFACE_H
