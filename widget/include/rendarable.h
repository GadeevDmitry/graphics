#ifndef RANDERABLE_H
#define RANDERABLE_H

#include "render_texture.h"

//==================================================================================================

class renderable
{
public:
    virtual ~renderable() {}
    virtual void render(render_texture_t *wnd) const = 0;
};

#endif // RANDERABLE_H
