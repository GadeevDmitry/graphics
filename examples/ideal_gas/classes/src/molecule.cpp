#include <iterator>
#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "color.h"
#include "circle.h"
#include "material_point.h"
#include "segment.h"
#include "molecule.h"
#include "rectangle.h"

#include "algorithm/algorithm.h"

//==================================================================================================

const double molecule_t::MOLECULE_SIZE = 3;
static vec2d get_vertical_segment_distance  (const vec2d &point, const segment_t &segment);
static vec2d get_horizontal_segment_distance(const vec2d &point, const segment_t &segment);

//==================================================================================================

static vec2d get_vertical_segment_distance(const vec2d &point, const segment_t &segment)
{
    assert(dblcmp(segment.endpoint_1.x, segment.endpoint_2.x) == 0);

    vec2d upper_endpoint = segment.endpoint_1.y > segment.endpoint_2.y ? segment.endpoint_1 : segment.endpoint_2;
    vec2d lower_endpoint = segment.endpoint_1.y > segment.endpoint_2.y ? segment.endpoint_2 : segment.endpoint_1;

    if (point.y <= lower_endpoint.y) return lower_endpoint - point;
    if (point.y >= upper_endpoint.y) return upper_endpoint - point;

    return vec2d(segment.endpoint_1.x - point.x, 0);
}

//--------------------------------------------------------------------------------------------------

static vec2d get_horizontal_segment_distance(const vec2d &point, const segment_t &segment)
{
    assert(dblcmp(segment.endpoint_1.y, segment.endpoint_2.y) == 0);

    vec2d r_endpoint = segment.endpoint_1.x > segment.endpoint_2.x ? segment.endpoint_1 : segment.endpoint_2;
    vec2d l_endpoint = segment.endpoint_1.x > segment.endpoint_2.x ? segment.endpoint_2 : segment.endpoint_1;

    if (point.x <= l_endpoint.x) return l_endpoint - point;
    if (point.x >= r_endpoint.x) return r_endpoint - point;

    return vec2d(0, segment.endpoint_1.y - point.y);
}

//--------------------------------------------------------------------------------------------------

bool molecule_t::try_hit_segment(const double frame_time, const segment_t &target)
{
    vec2d center_hit_distance;

    if      (dblcmp(target.endpoint_1.x, target.endpoint_2.x) == 0) center_hit_distance = get_vertical_segment_distance  (center.position, target);
    else if (dblcmp(target.endpoint_1.y, target.endpoint_2.y) == 0) center_hit_distance = get_horizontal_segment_distance(center.position, target);
    else { assert(false && "can't evaluate distance: not orthogonal segment\n"); }

//  printf("SEGMENT before normalization: center_hit_distance(%lg, %lg)\n", center_hit_distance.x, center_hit_distance.y);
    vec2d real_hit_distance = center_hit_distance.get_normalization(center_hit_distance.len() - MOLECULE_SIZE/2);
//  printf("SEGMENT after  normalization: real_hit_distance(%lg, %lg)\n", real_hit_distance.x, real_hit_distance.y);

    double speed_projection = (center.speed, center_hit_distance.get_normalization());
    double frame_distance   = speed_projection * frame_time;

    if (frame_distance < real_hit_distance.len())
        return false;

    double hit_time = real_hit_distance.len() / speed_projection;
    vec2d hit_point = center.position + center.speed * hit_time;

    vec2d hit_normal      = (target.endpoint_1 - target.endpoint_2).get_normal();
    vec2d reflected_speed = center.speed.get_reflection(hit_normal);

    center = material_point_t(hit_point, reflected_speed);
    return true;
}

//--------------------------------------------------------------------------------------------------

bool molecule_t::try_hit_piston(const double frame_time, const piston_t &target)
{
    assert(dblcmp(target.shape.endpoint_1.y, target.shape.endpoint_2.y) == 0);

    vec2d center_hit_distance = get_horizontal_segment_distance(center.position, target.shape);
//  printf("PISTON  before normalization: center_hit_distance(%lg, %lg)\n", center_hit_distance.x, center_hit_distance.y);
    assert(center_hit_distance == vec2d(0, target.shape.endpoint_1.y - center.position.y));

    vec2d real_hit_distance = center_hit_distance.get_normalization(center_hit_distance.len() - MOLECULE_SIZE/2);
//  printf("PISTON  after  normalization: real_hit_distance(%lg, %lg)\n", real_hit_distance.x, real_hit_distance.y);

    double molecule_speed_projection = (center.speed       ,  center_hit_distance.get_normalization());
    double piston_speed_projection   = (target.center.speed, -center_hit_distance.get_normalization());

    double frame_distance = (molecule_speed_projection + piston_speed_projection) * frame_time;

    if (frame_distance < real_hit_distance.len())
        return false;

    double hit_time = real_hit_distance.len() / (molecule_speed_projection + piston_speed_projection);
    vec2d hit_point = center.position + center.speed * hit_time;

    vec2d hit_normal      = (target.shape.endpoint_1 - target.shape.endpoint_2).get_normal();
    vec2d reflected_speed = center.speed.get_reflection(hit_normal) + 2*target.center.speed;

    center = material_point_t(hit_point, reflected_speed);
    return true;
}

//--------------------------------------------------------------------------------------------------

bool molecule_t::try_hit_molecule(const double frame_time, const molecule_t &target, vec2d &hit_point) const
{
    vec2d hit_distance = target.center.position - center.position;
    hit_distance = hit_distance.normalize(hit_distance.len() - MOLECULE_SIZE);

    double speed_1_projection = (center.speed       ,  hit_distance.get_normalization());
    double speed_2_projection = (target.center.speed, -hit_distance.get_normalization());

    double frame_distance = (speed_1_projection + speed_2_projection) * frame_time;

    if (frame_distance < hit_distance.len())
        return false;

    double k = speed_1_projection / (speed_1_projection + speed_2_projection);
    hit_point = center.position + k*hit_distance;

    return true;
}

//--------------------------------------------------------------------------------------------------

void heavy_molecule_t::draw(sf::RenderWindow &wnd) const
{
    vec2d       molecule_size(MOLECULE_SIZE, MOLECULE_SIZE);
    rectangle_t molecule_img (center.position - molecule_size/2,
                              center.position + molecule_size/2);

    draw_filled_rectangle(molecule_img, wnd, sf::Color::Cyan);
}

//--------------------------------------------------------------------------------------------------

void light_molecule_t::draw(sf::RenderWindow &wnd) const
{
    circle_t molecule_img(center.position, MOLECULE_SIZE);
    draw_filled_circle(molecule_img, wnd, sf::Color::Green);
}
