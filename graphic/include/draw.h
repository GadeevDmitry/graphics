#ifndef DRAW_H
#define DRAW_H

#include "vec2d.h"
#include "circle.h"
#include "segment.h"
#include "rectangle.h"
#include "coord_system.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

void draw_coord_sys(const coord_system &sys, sf::RenderWindow &wnd, const sf::Color &col);

inline void draw_vec2d(const vec2d &vec_beg, const vec2d &vec_main, const coord_system &sys, sf::RenderWindow &wnd, const sf::Color &col);
inline void draw_line (const vec2d &vec_beg, const vec2d &vec_main, const coord_system &sys, sf::RenderWindow &wnd, const sf::Color &col);

void        draw_hollow_rectangle(const rectangle_t &pix_rect, sf::RenderWindow &wnd, const sf::Color &outline_col);
void        draw_filled_rectangle(const rectangle_t &pix_rect, sf::RenderWindow &wnd, const sf::Color &outline_col, const sf::Color &fill_col);
inline void draw_filled_rectangle(const rectangle_t &pix_rect, sf::RenderWindow &wnd, const sf::Color &fill_col);

void        draw_filled_circle(const circle_t &pix_circle, sf::RenderWindow &wnd, const sf::Color &outline_col, const sf::Color &fill_col);
inline void draw_filled_circle(const circle_t &pix_circle, sf::RenderWindow &wnd, const sf::Color &fill_col);

inline void draw_segment(const segment_t &pix_seg, sf::RenderWindow &wnd, const sf::Color &col);

void draw_vec2d(const vec2d &pix_beg, const vec2d &pix_main, sf::RenderWindow &wnd, const sf::Color &col);
void draw_line (const vec2d &pix_beg, const vec2d &pix_main, sf::RenderWindow &wnd, const sf::Color &col);
void draw_point(const vec2d &pix_point                     , sf::RenderWindow &wnd, const sf::Color &col);

//==================================================================================================

inline void draw_vec2d(const vec2d &vec_beg, const vec2d &vec_main, const coord_system &sys,
                       sf::RenderWindow &wnd, const sf::Color &col)
{
    draw_vec2d(sys.get_off_from_rel(vec_beg), sys.get_abs_from_rel(vec_main), wnd, col);
}

//--------------------------------------------------------------------------------------------------

inline void draw_line(const vec2d &vec_beg, const vec2d &vec_main, const coord_system &sys,
                      sf::RenderWindow &wnd, const sf::Color &col)
{
    draw_line(sys.get_off_from_rel(vec_beg), sys.get_abs_from_rel(vec_main), wnd, col);
}

//--------------------------------------------------------------------------------------------------

inline void draw_filled_rectangle(const rectangle_t &pix_rect, sf::RenderWindow &wnd, const sf::Color &fill_col)
{
    return draw_filled_rectangle(pix_rect, wnd, fill_col, fill_col);
}

//--------------------------------------------------------------------------------------------------

inline void draw_filled_circle(const circle_t &pix_circle, sf::RenderWindow &wnd, const sf::Color &fill_col)
{
    return draw_filled_circle(pix_circle, wnd, fill_col, fill_col);
}

//--------------------------------------------------------------------------------------------------

inline void draw_segment(const segment_t &pix_seg, sf::RenderWindow &wnd, const sf::Color &col)
{
    draw_line (pix_seg.endpoint_1, pix_seg.endpoint_2 - pix_seg.endpoint_1, wnd, col);
    draw_point(pix_seg.endpoint_1, wnd, col);
    draw_point(pix_seg.endpoint_2, wnd, col);
}

#endif // DRAW_H
