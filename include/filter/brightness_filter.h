#ifndef BRIGHTNESS_FILTER_H
#define BRIGHTNESS_FILTER_H

#include "filter.h"

//==================================================================================================

class brightness_filter_t: public filter_t
{
// member functions
public:
    inline brightness_filter_t();

// virtual
public:
    virtual void apply(RenderTargetI *perm) override;

// member data
private:
    unsigned char brightness;
};

//--------------------------------------------------------------------------------------------------

inline brightness_filter_t::brightness_filter_t():
brightness(10)
{}

#endif // BRIGHTNESS_FILTER_H
