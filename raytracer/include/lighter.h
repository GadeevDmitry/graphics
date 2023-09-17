#ifndef LIGHTER_H
#define LIGHTER_H

#include "color.h"
#include "vec3d.h"

//==================================================================================================

class lighter_t
{
private:
    color_t own_col;
    vec3d   pos;

public:
    explicit lighter_t(const color_t &own_col_, const vec3d &pos_):
    own_col(own_col_),
    pos(pos_)
    {}

    color_t get_own_col() const { return own_col; }
    vec3d   get_pos    () const { return pos; }
};

#endif // LIGHTER_H
