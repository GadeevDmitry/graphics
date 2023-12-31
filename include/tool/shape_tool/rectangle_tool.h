#ifndef RECTANGLE_TOOL_H
#define RECTANGLE_TOOL_H

#include "tool/shape_tool.h"

//==================================================================================================

class rectangle_tool_t: public shape_tool_t
{
// member functions
public:
    inline rectangle_tool_t();

// virtual
protected:
    virtual void draw_temp(RenderTargetI *temp, Color color) override;
};

//--------------------------------------------------------------------------------------------------

inline rectangle_tool_t::rectangle_tool_t():
shape_tool_t()
{}

#endif // RECTANGLE_TOOL_H
