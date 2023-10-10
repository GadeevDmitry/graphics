#include <stdio.h>
#include "region.h"
#include "intersect.h"
#include "log.h"

//==================================================================================================

static void subtract_region_area   (list *const res, const list *const region, const rectangle_t *const area);
static void subtract_area_area     (list *const res, const rectangle_t  &op_1, const rectangle_t       &op_2);

static void intersect_region_region(list *const  op_1, const list *const  op_2);
static bool intersect_area_area    (rectangle_t &op_1, const rectangle_t &op_2);

//==================================================================================================

void clipping_region_t::dump(const void *clipping_region_)
{
    const clipping_region_t *clipping_region = (const clipping_region_t *) clipping_region_;

    LOG_TAB_SERVICE_MESSAGE("clipping_region_t (address: %p)\n{", "\n", clipping_region);
    LOG_TAB++;

    rectangle_t::dump(&clipping_region->region);
    list_dump        (&clipping_region->areas);

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");
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
    list_ctor(&res, sizeof(rectangle_t), nullptr, rectangle_t::dump);

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
    list_ctor(&temp, sizeof(rectangle_t), nullptr, rectangle_t::dump);

    rectangle_t *op_2_cur = (rectangle_t *) list_next(op_2_front);
    for (; op_2_cur != op_2_fict; op_2_cur = (rectangle_t *) list_next(op_2_cur))
    {
        subtract_region_area(&temp, &op_1.areas, op_2_cur);
//      LOG_TAB_MESSAGE("RES & TEMP BEFORE MERGING\n");
//      list_dump(&res);
//      list_dump(&temp);

        intersect_region_region(&res, &temp);
//      LOG_TAB_MESSAGE("RES AFTER MERGING\n");
//      list_dump(&res);

        list_clear(&temp);
        if (res.size == 0) break;
    }

    op_1.set_areas(&res);

    list_dtor(&res);
    list_dtor(&temp);

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

void clipping_region_t::render(render_texture_t &wnd, const vec2d &offset) const
{
    rectangle_t *front = (rectangle_t *) list_front(&areas);
    rectangle_t *fict  = (rectangle_t *) list_fict (&areas);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        wnd.draw_hollow_rectangle(*cur + offset, color_t::get_rand_color());
    }
}

//--------------------------------------------------------------------------------------------------

static void intersect_region_region(list *const op_1, const list *const op_2)
{
    if (op_2->size == 0)
    {
        list_clear(op_1);
        return;
    }

//  LOG_TAB_MESSAGE(">>>>>>>>>>>>>>>>>>>>>>>>>\n"
//                  "INTERSECTION\n"
//                  ">>>>>>>>>>>>>>>>>>>>>>>>>\n");

    rectangle_t *op_2_front = (rectangle_t *) list_front(op_2);
    rectangle_t *op_2_fict  = (rectangle_t *) list_fict (op_2);

    size_t initial_op_1_size = op_1->size;
    for (size_t i = 0; i < initial_op_1_size; ++i)
    {
        rectangle_t op_1_area = *(rectangle_t *) list_front(op_1);

        for (rectangle_t *op_2_area = op_2_front; op_2_area != op_2_fict;
             op_2_area = (rectangle_t *) list_next(op_2_area))
        {
//          LOG_TAB_MESSAGE("op_1_area\n");
//          rectangle_t::dump(&op_1_area);
//          LOG_TAB_MESSAGE("op_2_area\n");
//          rectangle_t::dump(op_2_area);

            rectangle_t op_1_area_dup = op_1_area;

            bool is_valid_area = intersect_area_area(op_1_area_dup, *op_2_area);
            if (is_valid_area)
                list_push_back(op_1, &op_1_area_dup);

//          LOG_TAB_MESSAGE("intersect\n");
//          if (is_valid_area)
//              rectangle_t::dump(&op_1_area);
//          else
//              LOG_TAB_MESSAGE("invalid\n");
        }

        list_pop_front(op_1);
    }

//  LOG_TAB_MESSAGE("<<<<<<<<<<<<<<<<<<<<<<<<<\n"
//                  "INTERSECTION\n"
//                  "<<<<<<<<<<<<<<<<<<<<<<<<<\n");
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
