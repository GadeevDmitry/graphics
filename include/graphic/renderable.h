#ifndef RANDERABLE_H
#define RANDERABLE_H

#include "region.h"
#include "render_texture.h"

//==================================================================================================

class renderable
{
// member functions
public:
             inline  renderable();
    explicit inline  renderable(const rectangle_t &enclosing);
    virtual  inline ~renderable() {}

// virtual
public:
    virtual void recalc_areas()                      = 0;
    virtual void render      (render_texture_t &wnd) = 0;

// member data
public:
    clipping_region_t visible;
};

//--------------------------------------------------------------------------------------------------

inline renderable::renderable():
visible()
{}

//--------------------------------------------------------------------------------------------------

inline renderable::renderable(const rectangle_t &enclosing):
visible(enclosing)
{}

#endif // RANDERABLE_H
