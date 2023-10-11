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

    inline       clipping_region_t &get_clipping_region();
    inline const rectangle_t       &get_object_region  () const;
    inline const list              &get_visible_areas  () const;

    virtual void recalc_region(const vec2d &offset = vec2d(0, 0)) = 0;
    virtual void render(render_texture_t &wnd, const vec2d &offset = vec2d(0, 0)) const = 0;
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

inline clipping_region_t &renderable::get_clipping_region()
{
    return visible;
}

//--------------------------------------------------------------------------------------------------

inline const rectangle_t &renderable::get_object_region() const
{
    return visible.get_region();
}

//--------------------------------------------------------------------------------------------------

inline const list &renderable::get_visible_areas() const
{
    return visible.get_areas();
}

#endif // RANDERABLE_H
