#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

#include "vec2d.h"
#include "coord_system.h"

//==================================================================================================

void draw_coord_sys(const coord_system &sys                    , sf::RenderWindow &wnd, const sf::Color &col);
void draw_vec2d    (const vec2d &pix_beg, const vec2d &pix_main, sf::RenderWindow &wnd, const sf::Color &col);
void draw_line     (const vec2d &pix_beg, const vec2d &pix_main, sf::RenderWindow &wnd, const sf::Color &col);
void draw_point    (const vec2d &pix_point                     , sf::RenderWindow &wnd, const sf::Color &col);

//--------------------------------------------------------------------------------------------------

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

#endif // DRAW_H
