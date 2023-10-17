#ifndef RANDERABLE_H
#define RANDERABLE_H

#include "region.h"
#include "render_texture.h"

//==================================================================================================

class renderable
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    clipping_region_t visible;

public:
    inline          renderable();
    inline explicit renderable(const rectangle_t &region_);
    virtual        ~renderable() {}

    virtual void   dump_region() const {};
    virtual void recalc_region() = 0;

    virtual void render(render_texture_t &wnd) = 0;
};

//--------------------------------------------------------------------------------------------------

inline renderable::renderable():
visible()
{}

//--------------------------------------------------------------------------------------------------

inline renderable::renderable(const rectangle_t &region_):
visible(region_)
{}

#endif // RANDERABLE_H
