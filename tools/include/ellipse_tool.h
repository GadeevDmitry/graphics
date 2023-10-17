#ifndef ELLIPSE_TOOL_H
#define ELLIPSE_TOOL_H

#include "shape_tool.h"

//==================================================================================================

class ellipse_tool_t: public shape_tool_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    void draw_temp(render_texture_t &temp, const color_t &color) override;

public:
    inline ellipse_tool_t();
};

//--------------------------------------------------------------------------------------------------

inline ellipse_tool_t::ellipse_tool_t():
shape_tool_t()
{}

#endif // ELLIPSE_TOOL_H
