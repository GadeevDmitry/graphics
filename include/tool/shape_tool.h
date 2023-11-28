#ifndef SHAPE_TOOL_H
#define SHAPE_TOOL_H

#include "tool.h"

//==================================================================================================

class shape_tool_t: public tool_t
{
// member functions
public:
    inline shape_tool_t();

// virtual
public:
    virtual void inline deactivate      (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) override;
    virtual void        paint_on_press  (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) override;
    virtual void        paint_on_release(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) override;
    virtual void        paint_on_move   (RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) override;

protected:
    virtual void draw_temp(RenderTargetI *temp, Color color) = 0;
};

//--------------------------------------------------------------------------------------------------

inline shape_tool_t::shape_tool_t():
tool_t()
{}

//--------------------------------------------------------------------------------------------------

inline void shape_tool_t::deactivate(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color)
{
    (void) perm;
    (void) local_context;
    (void) color;

    temp->clear();
}

#endif // SHAPE_TOOL_H
