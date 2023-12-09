#include <stdio.h>

#include "filter/russia_filter.h"
#include "plugin/standart/plugin.h"

//==================================================================================================

namespace
{
    class russia_filter_plugin_t: public plugin::Plugin, plugin::FilterI
    {
    // member functions
    public:
        explicit russia_filter_plugin_t(uint64_t id, const char *name);

    // virtual
    public:
        virtual plugin::Array<const char *> get_param_names()                             override { return filter.get_param_names(); }
        virtual plugin::Array<double>       get_params     ()                             override { return filter.get_params(); }
        virtual void                        set_params     (plugin::Array<double> params) override { return filter.set_params(params); }

        virtual void                        apply          (RenderTargetI *perm)          override { return filter.apply(perm); }

        virtual plugin::Interface          *get_interface  ()                             override { return &filter; }

    // member data
    private:
        russia_filter_t filter;
    };

    //--------------------------------------------------------------------------------------------------

    russia_filter_plugin_t::russia_filter_plugin_t(uint64_t id, const char *name):
    plugin::Plugin(id, name, plugin::InterfaceType::Filter),
    filter        ()
    {}
}

//==================================================================================================

static russia_filter_plugin_t instance(0x12345, "RUSSIA");

//==================================================================================================

extern "C" plugin::Plugin *getInstance(plugin::App *app)
{
    return &instance;
}
