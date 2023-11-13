#ifndef FILTER_H
#define FILTER_H

#include "graphic/render_texture.h"

//==================================================================================================

class filter_t
{
// member functions
public:
    virtual inline ~filter_t() {}

// virtual
public:
    virtual void apply(render_texture_t &perm) = 0;
};

#endif // FILTER_H
