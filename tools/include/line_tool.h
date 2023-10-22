#ifndef LINE_TOOL_H
#define LINE_TOOL_H

#include "shape_tool.h"

//==================================================================================================

class line_tool_t: public shape_tool_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    void draw_temp(render_texture_t &temp, const color_t &color) override;

public:
    inline line_tool_t();
};

//--------------------------------------------------------------------------------------------------

inline line_tool_t::line_tool_t():
shape_tool_t()
{}

#endif // RECTANGLE_TOOL_H
