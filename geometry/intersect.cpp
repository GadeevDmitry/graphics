#include <stdio.h>
#include "intersect.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

enum LINE_INTERS_TYPE
{
    NONE    ,
    POINT   ,
    SAME    ,
};

//==================================================================================================

static rectangle_t      get_intersect_rectangle_rectangle(const rectangle_t &rect_1, const rectangle_t &rect_2);
static bool             get_intersect_segment_rectangle  (const segment_t   &seg   , const rectangle_t &rect, segment_t &res);
static LINE_INTERS_TYPE get_intersect_segment_segment    (const segment_t   &seg1  , const segment_t   &seg2, vec2d &inters_point);

//==================================================================================================

static rectangle_t get_intersect_rectangle_rectangle(const rectangle_t &rect_1,
                                                     const rectangle_t &rect_2)
{
    return rectangle_t(vec2d::max(rect_1.ld_corner, rect_2.ld_corner),
                       vec2d::min(rect_1.ru_corner, rect_2.ru_corner));
}

//--------------------------------------------------------------------------------------------------

bool is_intersect_rectangle_rectangle(const rectangle_t &rect_1,
                                      const rectangle_t &rect_2)
{
    rectangle_t intersect = get_intersect_rectangle_rectangle(rect_1, rect_2);
    return      intersect.is_valid();
}

//--------------------------------------------------------------------------------------------------

bool intersect_rectangle_rectangle(      rectangle_t &rect_1,
                                   const rectangle_t &rect_2)
{
    rectangle_t intersect = get_intersect_rectangle_rectangle(rect_1, rect_2);
    if (!intersect.is_valid()) return false;

    rect_1 = intersect;
    return true;
}

//--------------------------------------------------------------------------------------------------

static LINE_INTERS_TYPE get_intersect_segment_segment(const segment_t &seg1, const segment_t &seg2, vec2d &inters_point)
{
    // build 1 segment a1x + b1y = c1
    double a1 = seg1.endpoint_2.y - seg1.endpoint_1.y;
    double b1 = seg1.endpoint_1.x - seg1.endpoint_2.x;
    double c1 = seg1.endpoint_1.x * a1 + seg1.endpoint_1.x * b1;

    // build 2 segment a2x + b2y = c2
    double a2 = seg2.endpoint_2.y - seg2.endpoint_1.y;
    double b2 = seg2.endpoint_1.x - seg2.endpoint_2.x;
    double c2 = seg2.endpoint_1.x * a2 + seg2.endpoint_1.y * b2;

    // x = (c1*b2 - c2*b1) / (a1*b2 - a2*b1)
    // y = (a1*c2 - a2*c1) / (a1*b2 - a2*b1)
    double delta = a1 * b2 - a2 * b1;

    // parallel case
    if (dblcmp(delta, 0) == 0)
    {
        inters_point = vec2d(0, 0);

        // lines are equal
        if (dblcmp(seg1.endpoint_1.x, seg2.endpoint_1.x) == 0 ||
            dblcmp(seg2.endpoint_1.y, seg2.endpoint_1.y) == 0)
            return SAME;

        return NONE;
    }

    double x = (c1 * b2 - c2 * b1) / delta;
    double y = (c2 * a1 - c1 * a2) / delta;

    inters_point = vec2d(x, y);

    // figure out that point is inside segment
    if (std::min(seg1.endpoint_1.x, seg1.endpoint_2.x) <= x && x <= std::max(seg1.endpoint_1.x, seg1.endpoint_2.x) &&
        std::min(seg1.endpoint_1.y, seg1.endpoint_2.y) <= y && y <= std::max(seg1.endpoint_1.y, seg1.endpoint_2.y))
        return POINT;

    return NONE;
}

//--------------------------------------------------------------------------------------------------

static bool get_intersect_segment_rectangle(const segment_t &seg, const rectangle_t &rect, segment_t &res)
{
    segment_t upper = segment_t(rect.lu_corner(), rect.ru_corner);
    segment_t down  = segment_t(rect.ld_corner  , rect.rd_corner());
    segment_t left  = segment_t(rect.lu_corner(), rect.ld_corner);
    segment_t right = segment_t(rect.ru_corner  , rect.rd_corner());

    vec2d segment_points[2];

    int point_cnt = 0;

    LINE_INTERS_TYPE inters_res = get_intersect_segment_segment(seg, upper, segment_points[point_cnt]);
    if (inters_res == SAME)
    {
        res = upper;
        return true;
    }
    else if (inters_res == POINT) point_cnt++;

    inters_res = get_intersect_segment_segment(seg, down, segment_points[point_cnt]);
    if (inters_res == SAME)
    {
        res = down;
        return true;
    }
    else if (inters_res == POINT)
    {
        point_cnt++;
        if (point_cnt == 2)
        {
            res = segment_t(segment_points[0], segment_points[1]);
            return true;
        }
    }

    inters_res = get_intersect_segment_segment(seg, left, segment_points[point_cnt]);
    if (inters_res == SAME)
    {
        res = left;
        return true;
    }
    else if (inters_res == POINT)
    {
        point_cnt++;
        if (point_cnt == 2)
        {
            res = segment_t(segment_points[0], segment_points[1]);
            return true;
        }
    }

    inters_res = get_intersect_segment_segment(seg, right, segment_points[point_cnt]);
    if (inters_res == SAME)
    {
        res = right;
        return true;
    }
    else if (inters_res == POINT)
    {
        point_cnt++;
        if (point_cnt == 2)
        {
            res = segment_t(segment_points[0], segment_points[1]);
            return true;
        }
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool is_intersect_line_rectangle(const segment_t &seg, const rectangle_t &rect)
{
    segment_t res = segment_t();
    return get_intersect_segment_rectangle(seg, rect, res);
}

//--------------------------------------------------------------------------------------------------

bool intersect_line_rectangle(segment_t &seg, const rectangle_t &rect)
{
    segment_t res = segment_t();
    if (!get_intersect_segment_rectangle(seg, rect, res)) return false;

    seg = res;
    return true;
}
