#ifndef REGION_H
#define REGION_H

#include "list.h"
#include "rectangle.h"

//==================================================================================================

class render_texture_t;

class clipping_region_t
{
private:
    rectangle_t region;
    list        areas;

    void set_areas(const list *const  areas_);

public:
    inline          clipping_region_t();
    inline explicit clipping_region_t(const rectangle_t &region_);
    inline         ~clipping_region_t();

    inline bool               set_region(const rectangle_t &region_);
    inline const rectangle_t &get_region() const;
    inline const list        &get_areas () const;

    inline void reset();
    void render(render_texture_t &wnd, const vec2d &offset = vec2d(0, 0)) const;

    friend clipping_region_t &operator -=(clipping_region_t &op_1, const clipping_region_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const clipping_region_t &op_2);

    friend clipping_region_t &operator -=(clipping_region_t &op_1, const rectangle_t &op_2);
    friend clipping_region_t &operator *=(clipping_region_t &op_1, const rectangle_t &op_2);

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

inline const rectangle_t &clipping_region_t::get_region() const
{
    return region;
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
