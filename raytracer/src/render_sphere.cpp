#include <stdio.h>
#include <stdlib.h>

#include "render_sphere.h"
#include "equation_solver.h"
#include "vec3d.h"
#include "ray.h"

#include "algorithm/algorithm.h"

//==================================================================================================

bool render_sphere_t::get_intersection(const ray_t &ray, vec3d &intersect_pt) const
{
    // Уравнение луча:
    // x = xs + t * xd
    // y = ys + t * yd
    // z = zs + t * zd
    //
    // Уравнение сферы:
    // (x - xc)^2 + (y - yc)^2 + (z - zc)^2 = r^2

    double t_1 = 0, t_2 = 0;

    vec3d distance   = ray.get_start() - center;
    int square_solve = square_solver(ray.get_dir().len2(), 2*(ray.get_dir(), distance), distance.len2() - radius*radius, t_1, t_2);

    if (square_solve != 2 || t_1 <= 0 || t_2 <= 0) return false;

    double t = t_1 < t_2 ? t_1 : t_2;
    intersect_pt = ray.get_start() + t*ray.get_dir();

    return true;
}

//--------------------------------------------------------------------------------------------------

bool render_sphere_t::is_on_surface(const vec3d &pt) const
{
    double distance2 = (pt - center).len2();
    return dblcmp(distance2, radius*radius) == 0;
}
