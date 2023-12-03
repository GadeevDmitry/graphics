#ifndef FILTER_H
#define FILTER_H

#include "plugin/standart/Filter.h"
#include "graphic/render_texture.h"

//==================================================================================================

using plugin::FilterI;
using plugin::RenderTargetI;

class filter_t: public FilterI
{
// member functions
public:
    virtual inline ~filter_t() {}

// virtual
public:
    virtual plugin::Array<const char *> inline get_param_names()                             override;
    virtual plugin::Array<double>       inline get_params     ()                             override;
    virtual void                        inline set_params     (plugin::Array<double> params) override;
};

//--------------------------------------------------------------------------------------------------

inline plugin::Array<const char *> filter_t::get_param_names()
{
    return plugin::Array<const char *>(0, nullptr);
}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<double> filter_t::get_params()
{
    return plugin::Array<double>(0, nullptr);
}

//--------------------------------------------------------------------------------------------------

inline void filter_t::set_params(plugin::Array<double> params)
{
    (void) params;
}

#endif // FILTER_H
