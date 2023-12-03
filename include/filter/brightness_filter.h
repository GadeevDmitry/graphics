#ifndef BRIGHTNESS_FILTER_H
#define BRIGHTNESS_FILTER_H

#include "filter.h"
#include "data_structs/include/log.h"

//==================================================================================================

class brightness_filter_t: public filter_t
{
// member functions
public:
    inline brightness_filter_t();

// virtual
public:
    virtual plugin::Array<const char *> inline get_param_names()                             override;
    virtual plugin::Array<double>       inline get_params     ()                             override;
    virtual void                        inline set_params     (plugin::Array<double> params) override;

    virtual void apply(RenderTargetI *perm) override;

// member data
private:
    unsigned char brightness;
};

//--------------------------------------------------------------------------------------------------

inline brightness_filter_t::brightness_filter_t():
filter_t  (),
brightness(10)
{}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<const char *> brightness_filter_t::get_param_names()
{
    const char **param_names = new const char *[1];
    param_names[0] = "[1 - 255] brightness";

    return plugin::Array<const char *>(1, param_names);
}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<double> brightness_filter_t::get_params()
{
    double *params = new double[1];
    params[0] = brightness;

    return plugin::Array<double>(1, params);
}

//--------------------------------------------------------------------------------------------------

inline void brightness_filter_t::set_params(plugin::Array<double> params)
{
    LOG_VERIFY(params.size == 1, (void) 0);
    brightness = (unsigned char) params.data[0];
}

#endif // BRIGHTNESS_FILTER_H
