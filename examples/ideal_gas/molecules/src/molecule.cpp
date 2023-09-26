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

bool molecule_t::try_hit_segment(const double frame_time, const segment_t &target,
                                 const vec2d &target_speed, double &hit_impulse)
{
    vec2d  distance_direct = distance_circle_segment(shape, target);
    double distance_len    = distance_direct.len();
    log_assert(dblcmp(distance_len, 0) != 0);

    double approcach_speed = get_approcach_speed(distance_direct, distance_len, speed, target_speed);
    if (approcach_speed < 0) return false;

    double real_distance_len = distance_len - shape.radius;
    real_distance_len = real_distance_len < 0 ? 0 : real_distance_len;
    if (approcach_speed * frame_time < real_distance_len) return false;

    double hit_time       = (dblcmp(real_distance_len, 0) == 0) ? 0 : real_distance_len / approcach_speed;
    double impulse_before = weight * abs((speed, target.get_normal())) / target.get_normal().len();

    shape.center += hit_time * speed;

    speed -= target_speed;
    speed.reflect(target.get_normal());
    speed += target_speed;

    shape.center += (frame_time - hit_time) * speed;

    double impulse_after = weight * abs((speed, target.get_normal())) / target.get_normal().len();
    hit_impulse = impulse_after + impulse_after;

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
