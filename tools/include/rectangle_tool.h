#ifndef RECTANGLE_TOOL_H
#define RECTANGLE_TOOL_H

#include "shape_tool.h"

//==================================================================================================

class rectangle_tool_t: public shape_tool_t
{
///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
private:
    void draw_temp(render_texture_t &temp, const color_t &color) override;

public:
    inline rectangle_tool_t();
};

//--------------------------------------------------------------------------------------------------

inline rectangle_tool_t::rectangle_tool_t():
shape_tool_t()
{}

#endif // RECTANGLE_TOOL_H
