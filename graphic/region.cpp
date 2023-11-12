#include <stdio.h>
#include "region.h"
#include "render_texture.h"
#include "geometry/intersect.h"
#include "data_structs/include/log.h"

//==================================================================================================

static void subtract_region_area   (list *const res, const list *const region, const rectangle_t *const area);
static void subtract_area_area     (list *const res, const rectangle_t  &op_1, const rectangle_t       &op_2);

static void intersect_region_region(list *const  op_1, const list *const  op_2);
static void intersect_region_area  (list *const  op_1, const rectangle_t &op_2);
static bool intersect_area_area    (rectangle_t &op_1, const rectangle_t &op_2);

//==================================================================================================

bool clipping_region_t::is_point_inside(const vec2d &point) const
{
    if (areas.size == 0) return false;

    rectangle_t *front = (rectangle_t *) list_front(&areas);
    rectangle_t *fict  = (rectangle_t *) list_fict (&areas);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur->is_point_inside(point)) return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

void clipping_region_t::dump() const
{
    LOG_TAB_SERVICE_MESSAGE("clipping_region\n{", "\n");
    LOG_TAB++;

    rectangle_t *front = (rectangle_t *) list_front(&areas);
    rectangle_t *fict  = (rectangle_t *) list_fict (&areas);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        cur->dump();
    }

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n\n");
}

//--------------------------------------------------------------------------------------------------

void clipping_region_t::set_areas(const list *const areas_)
{
    list_clear(&areas);

    rectangle_t *front = (rectangle_t *) list_front(areas_);
    rectangle_t *fict  = (rectangle_t *) list_fict (areas_);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        list_push_back(&areas, cur);
    }
}

//--------------------------------------------------------------------------------------------------

clipping_region_t &operator -=(clipping_region_t &op_1, const clipping_region_t &op_2)
{
    if (op_1.areas.size == 0) return op_1;
    if (op_2.areas.size == 0) return op_1;

    list res = {};
    list_ctor(&res, sizeof(rectangle_t));

    rectangle_t *op_2_front = (rectangle_t *) list_front(&op_2.areas);
    rectangle_t *op_2_fict  = (rectangle_t *) list_fict (&op_2.areas);

    subtract_region_area(&res, &op_1.areas, op_2_front);
    if (op_2.areas.size == 1)
    {
        op_1.set_areas(&res);
        list_dtor(&res);
        return op_1;
    }

    list temp = {};
    list_ctor(&temp, sizeof(rectangle_t));

    rectangle_t *op_2_cur = (rectangle_t *) list_next(op_2_front);
    for (; op_2_cur != op_2_fict; op_2_cur = (rectangle_t *) list_next(op_2_cur))
    {
        subtract_region_area(&temp, &op_1.areas, op_2_cur);
        intersect_region_region(&res, &temp);

        list_clear(&temp);
        if (res.size == 0) break;
    }

    op_1.set_areas(&res);

    list_dtor(&res);
    list_dtor(&temp);

    return op_1;
}

//--------------------------------------------------------------------------------------------------

clipping_region_t &operator +=(clipping_region_t &op_1, const clipping_region_t &op_2)
{
    if (op_2.areas.size == 0) return op_1;
    if (op_1.areas.size == 0)
    {
        op_1.set_areas(&op_2.areas);
        return op_1;
    }

    rectangle_t *op_2_front = (rectangle_t *) list_front(&op_2.areas);
    rectangle_t *op_2_fict  = (rectangle_t *) list_fict (&op_2.areas);

    for (rectangle_t *op_2_cnt = op_2_front; op_2_cnt != op_2_fict;
         op_2_cnt = (rectangle_t *) list_next(op_2_cnt))
    {
        list_push_back(&op_1.areas, op_2_cnt);
    }

    return op_1;
}

//--------------------------------------------------------------------------------------------------

clipping_region_t &operator *=(clipping_region_t &op_1, const clipping_region_t &op_2)
{
    if (op_1.areas.size == 0) return op_1;
    if (op_2.areas.size == 0)
    {
        list_clear(&op_1.areas);
        return op_1;
    }

    intersect_region_region(&op_1.areas, &op_2.areas);
    return op_1;
}

//--------------------------------------------------------------------------------------------------

clipping_region_t &operator |=(clipping_region_t &op_1, const clipping_region_t &op_2)
{
    if (op_2.areas.size == 0) return op_1;
    if (op_1.areas.size == 0)
    {
        op_1.set_areas(&op_2.areas);
        return op_1;
    }

    clipping_region_t temp;
    temp.set_areas(&op_2.areas);
    temp -= op_1;

    op_1 += temp;
    return op_1;
}

//--------------------------------------------------------------------------------------------------

clipping_region_t &operator -=(clipping_region_t &op_1, const rectangle_t &op_2)
{
    if (op_1.areas.size == 0) return op_1;

    list res = {};
    list_ctor(&res, sizeof(rectangle_t), nullptr);
    subtract_region_area(&res, &op_1.areas, &op_2);

    op_1.set_areas(&res);
    list_dtor     (&res);

    return op_1;
}

//--------------------------------------------------------------------------------------------------

clipping_region_t &operator *=(clipping_region_t &op_1, const rectangle_t &op_2)
{
    if (op_1.areas.size == 0) return op_1;

    intersect_region_area(&op_1.areas, op_2);
    return op_1;
}

//--------------------------------------------------------------------------------------------------

static void intersect_region_region(list *const op_1, const list *const op_2)
{
    if (op_2->size == 0)
    {
        list_clear(op_1);
        return;
    }

    rectangle_t *op_2_front = (rectangle_t *) list_front(op_2);
    rectangle_t *op_2_fict  = (rectangle_t *) list_fict (op_2);

    size_t initial_op_1_size = op_1->size;
    for (size_t i = 0; i < initial_op_1_size; ++i)
    {
        rectangle_t op_1_area = *(rectangle_t *) list_front(op_1);

        for (rectangle_t *op_2_area = op_2_front; op_2_area != op_2_fict;
             op_2_area = (rectangle_t *) list_next(op_2_area))
        {
            rectangle_t op_1_area_dup = op_1_area;

            bool is_valid_area = intersect_area_area(op_1_area_dup, *op_2_area);
            if (is_valid_area)
                list_push_back(op_1, &op_1_area_dup);
        }

        list_pop_front(op_1);
    }
}

//--------------------------------------------------------------------------------------------------

static void intersect_region_area(list *const op_1, const rectangle_t &op_2)
{
    size_t initial_op_1_size = op_1->size;
    for (size_t i = 0; i < initial_op_1_size; ++i)
    {
        rectangle_t op_1_area = *(rectangle_t *) list_front(op_1);

        bool is_valid_area = intersect_area_area(op_1_area, op_2);
        if (is_valid_area)
            list_push_back(op_1, &op_1_area);

        list_pop_front(op_1);
    }
}

//--------------------------------------------------------------------------------------------------

static bool intersect_area_area(rectangle_t &op_1, const rectangle_t &op_2)
{
    return intersect_rectangle_rectangle(op_1, op_2);
}

//--------------------------------------------------------------------------------------------------

static void subtract_region_area(list *const res, const list *const region, const rectangle_t *const area)
{
    rectangle_t *front = (rectangle_t *) list_front(region);
    rectangle_t *fict  = (rectangle_t *) list_fict (region);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        subtract_area_area(res, *cur, *area);
    }
}

//--------------------------------------------------------------------------------------------------

static void subtract_area_area(list *const res, const rectangle_t &op_1, const rectangle_t &op_2)
{
    if (!is_intersect_rectangle_rectangle(op_1, op_2))
    {
        list_push_back(res, &op_1);
        return;
    }

    if (op_1.ld_corner.x < op_2.ld_corner.x)
    {
        rectangle_t sub_area(op_1.ld_corner, vec2d(op_2.ld_corner.x, op_1.ru_corner.y));
        list_push_back(res, &sub_area);
    }

    double l_bound = std::max(op_1.ld_corner.x, op_2.ld_corner.x);
    double r_bound = std::min(op_1.ru_corner.x, op_2.ru_corner.x);

    if (op_1.ru_corner.y > op_2.ru_corner.y)
    {
        rectangle_t sub_area(vec2d(l_bound, op_2.ru_corner.y), vec2d(r_bound, op_1.ru_corner.y));
        list_push_back(res, &sub_area);
    }

    if (op_1.ld_corner.y < op_2.ld_corner.y)
    {
        rectangle_t sub_area(vec2d(l_bound, op_1.ld_corner.y), vec2d(r_bound, op_2.ld_corner.y));
        list_push_back(res, &sub_area);
    }

    if (op_1.ru_corner.x > op_2.ru_corner.x)
    {
        rectangle_t sub_area(vec2d(op_2.ru_corner.x, op_1.ld_corner.y), op_1.ru_corner);
        list_push_back(res, &sub_area);
    }
}
