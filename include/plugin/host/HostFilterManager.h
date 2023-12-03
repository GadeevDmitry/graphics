#ifndef PLUGIN_HOST_FILTER_MANAGER_H
#define PLUGIN_HOST_FILTER_MANAGER_H

#include "plugin/standart/Filter.h"
#include "filter/filter_manager.h"

//==================================================================================================

using plugin::FilterI;
using plugin::RenderTargetI;

namespace host
{
    class HostFilterManagerI: public plugin::FilterManagerI
    {
    // member functions
    public:
        explicit inline HostFilterManagerI(filter_manager_t &filter_manager);

    // virtual
    public:
        virtual inline void set_render_target(RenderTargetI *target) override;
        virtual inline void set_filter       (FilterI       *filter) override;
        virtual inline void apply_filter     ()                      override;

    // member data
    private:
        RenderTargetI    *target;        
        filter_manager_t &filter_manager;
    };

    //--------------------------------------------------------------------------------------------------

    inline HostFilterManagerI::HostFilterManagerI(filter_manager_t &filter_manager_):
    target        (nullptr),
    filter_manager(filter_manager_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline void HostFilterManagerI::set_render_target(RenderTargetI *target_)
    {
        target = target_;
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostFilterManagerI::set_filter(FilterI *filter)
    {
        filter_manager.set_filter(filter);
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostFilterManagerI::apply_filter()
    {
        filter_manager.last_filter->apply(target);
    }
};

#endif // PLUGIN_HOST_FILTER_MANAGER_H
