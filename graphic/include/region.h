#ifndef REGION_H
#define REGION_H

#include "list.h"
#include "rectangle.h"

//==================================================================================================

class clipping_region_t
{
private:
    list areas;
    void set_areas(const list *const areas_);

public:
    rectangle_t region;

    inline          clipping_region_t();
    inline explicit clipping_region_t(const rectangle_t &region_);
    inline         ~clipping_region_t();

    inline const list &get_areas() const;

    inline void reset();
    static void dump (const void *clipping_region_);

    friend clipping_region_t &operator -=(clipping_region_t &op_1, const clipping_region_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const clipping_region_t &op_2);

    friend clipping_region_t &operator -=(clipping_region_t &op_1, const rectangle_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const rectangle_t &op_2);

    friend clipping_region_t  operator + (const clipping_region_t &op_1, const vec2d &op_2);
    friend clipping_region_t  operator - (const clipping_region_t &op_1, const vec2d &op_2);
};

//--------------------------------------------------------------------------------------------------

inline clipping_region_t::clipping_region_t():
region()
{
    list_ctor(&areas, sizeof(rectangle_t), nullptr, rectangle_t::dump);
}

//--------------------------------------------------------------------------------------------------

inline clipping_region_t::clipping_region_t(const rectangle_t &region_):
region(region_)
{
    list_ctor(&areas, sizeof(rectangle_t), nullptr, rectangle_t::dump);
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

inline void clipping_region_t::reset()
{
    list_clear(&areas);
    list_push_back(&areas, &region);
}

#endif // REGION_H
