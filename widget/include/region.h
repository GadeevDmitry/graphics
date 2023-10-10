#ifndef REGION_H
#define REGION_H

#include "list.h"
#include "rectangle.h"

//==================================================================================================

class clipping_region_t
{
private:
    rectangle_t region;
    list        areas;

public:
    inline          clipping_region_t();
    inline explicit clipping_region_t(const rectangle_t &region_);
    inline         ~clipping_region_t();

    inline bool set_region(const rectangle_t &region_);
           void set_areas (const list *const  areas_);
    inline bool push_area (const rectangle_t &area);

    inline void clear();
    inline void reset();

    inline list        getAreas () const;
    inline rectangle_t getRegion() const;

    friend clipping_region_t &operator -=(clipping_region_t &op_1, const clipping_region_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const clipping_region_t &op_2);

    static void dump(const void *clipping_region_);
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
    list_push_front(&areas, &region_);
}

//--------------------------------------------------------------------------------------------------

inline clipping_region_t::~clipping_region_t()
{
    list_dtor(&areas);
}

//--------------------------------------------------------------------------------------------------

inline bool clipping_region_t::set_region(const rectangle_t &region_)
{
    region = region_;
    return list_push_front(&areas, &region_);
}

//--------------------------------------------------------------------------------------------------

inline bool clipping_region_t::push_area(const rectangle_t &area)
{
    return list_push_back(&areas, &area);
}

//--------------------------------------------------------------------------------------------------

inline void clipping_region_t::clear()
{
    list_clear(&areas);
}

//--------------------------------------------------------------------------------------------------

inline void clipping_region_t::reset()
{
    list_clear(&areas);
    list_push_back(&areas, &region);
}

//--------------------------------------------------------------------------------------------------

inline list clipping_region_t::getAreas() const {
    return areas;
}

//--------------------------------------------------------------------------------------------------

inline rectangle_t clipping_region_t::getRegion() const {
    return region;
}

#endif // REGION_H
