#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "distance.h"
#include "molecule.h"
#include "algorithm/algorithm.h"

//==================================================================================================

inline double get_approcach_speed(const vec2d &distance_direct, const double distance_len,
                                  const vec2d &speed_source, const vec2d &speed_dest)
{
    double speed_source_projection = ( distance_direct, speed_source) / distance_len;
    double speed_dest_projection   = (-distance_direct, speed_dest  ) / distance_len;

    return speed_source_projection + speed_dest_projection;
}

//--------------------------------------------------------------------------------------------------

bool molecule_t::try_hit_segment(const double frame_time, const segment_t &target, const vec2d &target_speed)
{
    vec2d  distance_direct = distance_circle_segment(shape, target);
    double distance_len    = distance_direct.len();
    assert(dblcmp(distance_len, shape.radius) >= 0);

//  printf("segment  = {(%lg, %lg), (%lg, %lg)}\n", target.endpoint_1.x, target.endpoint_1.y, target.endpoint_2.x, target.endpoint_2.y);
//  printf("center   =  {%lg, %lg}\n", shape.center.x, shape.center.y);

//  printf("distance = %lg\n", distance_len);

    double approcach_speed   = get_approcach_speed(distance_direct, distance_len, speed, target_speed);
    double real_distance_len = distance_len - shape.radius;

    if (approcach_speed * frame_time < real_distance_len) return false;

    double hit_time = real_distance_len / approcach_speed;

    shape.center += hit_time * speed;

    vec2d molecule_rel_speed = speed - target_speed;
    molecule_rel_speed.reflect(target.get_normal());
    speed = molecule_rel_speed + target_speed;

    shape.center += (frame_time - hit_time) * speed;

    return true;
}

//--------------------------------------------------------------------------------------------------

bool molecule_t::try_hit_circle(const double frame_time, const circle_t &target, const vec2d &target_speed,
                                double &hit_time) const
{
    vec2d  distance_direct = distance_circle_circle(shape, target);
    double distance_len    = distance_direct.len();
    if (dblcmp(distance_len, 0) == 0) return false;

    double approcach_speed = get_approcach_speed(distance_direct, distance_len, speed, target_speed);
    if (approcach_speed < 0) return false;

    double real_distance_len = distance_len - (shape.radius + target.radius);

    if (dblcmp(real_distance_len, 0) <= 0)                return false;
    if (approcach_speed * frame_time < real_distance_len) return false;

    hit_time = real_distance_len / approcach_speed;
    return true;
}
