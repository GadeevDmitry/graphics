#ifndef REGION_H
#define REGION_H

#include "geometry/rectangle.h"
#include "data_structs/include/list.h"

//==================================================================================================

class clipping_region_t
{
// member functions
public:
    explicit inline  clipping_region_t(const rectangle_t &enclosing = rectangle_t());
             inline ~clipping_region_t();

    const list inline &get_areas  () const;
    void       inline  reset_areas();

private:
    void set_areas(const list *const areas);

// member data
public:
    rectangle_t enclosing;
private:
    list        areas;

// friends
    friend clipping_region_t &operator -=(clipping_region_t &op_1, const clipping_region_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const clipping_region_t &op_2);

    friend clipping_region_t &operator -=(clipping_region_t &op_1, const rectangle_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const rectangle_t &op_2);

    friend clipping_region_t  operator + (const clipping_region_t &op_1, const vec2d &op_2);
    friend clipping_region_t  operator - (const clipping_region_t &op_1, const vec2d &op_2);
};

//--------------------------------------------------------------------------------------------------

inline clipping_region_t::clipping_region_t(const rectangle_t &enclosing_):
enclosing(enclosing_)
{
    list_ctor(&areas, sizeof(rectangle_t));
}

//--------------------------------------------------------------------------------------------------

inline clipping_region_t::~clipping_region_t()
{
    list_dtor(&areas);
}

//--------------------------------------------------------------------------------------------------

inline const list &clipping_region_t::get_areas() const
{
    return areas;
}

//--------------------------------------------------------------------------------------------------

inline void clipping_region_t::reset_areas()
{
    list_clear    (&areas);
    list_push_back(&areas, &enclosing);
}

#endif // REGION_H
