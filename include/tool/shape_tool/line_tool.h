#ifndef LINE_TOOL_H
#define LINE_TOOL_H

#include "tool/shape_tool.h"

//==================================================================================================

class line_tool_t: public shape_tool_t
{
// member functions
public:
    inline line_tool_t();

// virtual
protected:
    virtual void draw_temp(RenderTargetI *temp, Color color) override;
};

//--------------------------------------------------------------------------------------------------

inline line_tool_t::line_tool_t():
shape_tool_t()
{}

#endif // RECTANGLE_TOOL_H
