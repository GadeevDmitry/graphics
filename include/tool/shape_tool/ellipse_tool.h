#ifndef ELLIPSE_TOOL_H
#define ELLIPSE_TOOL_H

#include "tool/shape_tool.h"

//==================================================================================================

class ellipse_tool_t: public shape_tool_t
{
// member functions
public:
    inline ellipse_tool_t();

// virtual
protected:
    virtual void draw_temp(RenderTargetI *temp, Color color) override;
};

//--------------------------------------------------------------------------------------------------

inline ellipse_tool_t::ellipse_tool_t():
shape_tool_t()
{}

#endif // ELLIPSE_TOOL_H
