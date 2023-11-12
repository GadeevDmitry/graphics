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

    void inline reset_regions();

protected:
    void dump() const;

// virtual
public:
    virtual void recalc_regions()                      = 0;
    virtual void render        (render_texture_t &wnd) = 0;

// member data
public:
    rectangle_t       enclosing;
    clipping_region_t own_visible;
    clipping_region_t sub_enclosing;
};

//--------------------------------------------------------------------------------------------------

inline renderable::renderable():
enclosing    (rectangle_t()),
own_visible  (),
sub_enclosing()
{}

//--------------------------------------------------------------------------------------------------

inline renderable::renderable(const rectangle_t &enclosing_):
enclosing    (enclosing_),
own_visible  (),
sub_enclosing()
{}

//--------------------------------------------------------------------------------------------------

inline void renderable::reset_regions()
{
    own_visible  .reset_areas(enclosing);
    sub_enclosing.reset_areas(enclosing);
}

#endif // RANDERABLE_H
