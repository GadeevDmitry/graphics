#ifndef RUSSIA_FILTER_H
#define RUSSIA_FILTER_H

#include "filter.h"
#include "data_structs/include/log.h"

//==================================================================================================

class russia_filter_t: public filter_t
{
// member functions
public:
    inline russia_filter_t();
private:
    void pixel_blending(plugin::Color &pixel, const color_t &background_color);

// virtual
public:
    virtual plugin::Array<const char *> inline get_param_names()                             override;
    virtual plugin::Array<double>       inline get_params     ()                             override;
    virtual void                        inline set_params     (plugin::Array<double> params) override;

    virtual void apply(RenderTargetI *perm) override;

// member data
private:
    unsigned char power;
};

//--------------------------------------------------------------------------------------------------

inline russia_filter_t::russia_filter_t():
filter_t(),
power   (20)
{}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<const char *> russia_filter_t::get_param_names()
{
    static const char *param_names[1] = {"[10 - 255] power"};
    return plugin::Array<const char *>(1, param_names);
}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<double> russia_filter_t::get_params()
{
    static double params[1] = {};
    params[0] = (double) power;

    return plugin::Array<double>(1, params);
}

//--------------------------------------------------------------------------------------------------

inline void russia_filter_t::set_params(plugin::Array<double> params)
{
    LOG_VERIFY(params.size == 1, (void) 0);
    power = std::max((unsigned char) 10, (unsigned char) params.data[0]);
}

#endif // RUSSIA_FILTER_H
