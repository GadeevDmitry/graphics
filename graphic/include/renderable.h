#ifndef RANDERABLE_H
#define RANDERABLE_H

#include "region.h"
#include "render_texture.h"

//==================================================================================================

class renderable
{
protected:
    clipping_region_t visible;

public:
    inline          renderable();
    inline explicit renderable(const rectangle_t &region_);
    virtual        ~renderable() {}

    inline const clipping_region_t &get_visible() const;

    virtual void recalc_region() = 0;
    virtual void render(render_texture_t &wnd) const = 0;
};

//--------------------------------------------------------------------------------------------------

inline renderable::renderable():
visible()
{}

//--------------------------------------------------------------------------------------------------

inline renderable::renderable(const rectangle_t &region_):
visible(region_)
{}

//--------------------------------------------------------------------------------------------------

inline const clipping_region_t &renderable::get_visible() const
{
    return visible;
}

#endif // RANDERABLE_H
