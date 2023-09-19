#include <stdio.h>
#include "draw.h"

//==================================================================================================

static const unsigned VEC_ARROW_LEN = 20;
static const unsigned POINT_RADIUS  = 3;

//==================================================================================================

void draw_coord_sys(const coord_system &sys, sf::RenderWindow &wnd, const sf::Color &col)
{
    sf::Vector2u wnd_size = wnd.getSize();
    double wnd_x = wnd_size.x;
    double wnd_y = wnd_size.y;

    draw_vec2d(vec2d(0, sys.center.y)    , vec2d(wnd_x, 0) , wnd, col);
    draw_vec2d(vec2d(sys.center.x, wnd_y), vec2d(0, -wnd_y), wnd, col);

    for (double pix_x = sys.center.x; pix_x > 0    ; pix_x -= sys.unit.x) draw_point(vec2d(pix_x, sys.center.y), wnd, col);
    for (double pix_x = sys.center.x; pix_x < wnd_x; pix_x += sys.unit.x) draw_point(vec2d(pix_x, sys.center.y), wnd, col);

    for (double pix_y = sys.center.y; pix_y > 0    ; pix_y -= sys.unit.y) draw_point(vec2d(sys.center.x, pix_y), wnd, col);
    for (double pix_y = sys.center.y; pix_y < wnd_y; pix_y += sys.unit.y) draw_point(vec2d(sys.center.x, pix_y), wnd, col);
}

//--------------------------------------------------------------------------------------------------

void draw_vec2d(const vec2d &pix_beg, const vec2d &pix_main, sf::RenderWindow &wnd, const sf::Color &col)
{
    vec2d pix_end     = pix_beg + pix_main;
    vec2d pix_reverse = -pix_main;
    vec2d pix_norm    = pix_reverse.get_normal() / 3;

    vec2d fst_arr = (pix_reverse + pix_norm).get_normalization(VEC_ARROW_LEN);
    vec2d sec_arr = (pix_reverse - pix_norm).get_normalization(VEC_ARROW_LEN);

    draw_line(pix_beg, pix_main, wnd, col);
    draw_line(pix_end, fst_arr , wnd, col);
    draw_line(pix_end, sec_arr , wnd, col);
}

//--------------------------------------------------------------------------------------------------

void draw_line(const vec2d &pix_beg, const vec2d &pix_main, sf::RenderWindow &wnd, const sf::Color &col)
{
    vec2d pix_end = pix_beg + pix_main;
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(pix_beg.x, pix_beg.y), col),
                         sf::Vertex(sf::Vector2f(pix_end.x, pix_end.y), col)};

    wnd.draw(line, 2, sf::Lines);
}

//--------------------------------------------------------------------------------------------------

void draw_point(const vec2d &pix_point, sf::RenderWindow &wnd, const sf::Color &col)
{
    sf::CircleShape point;
    point.setRadius(POINT_RADIUS);
    point.setFillColor(col);
    point.setPosition(pix_point.x - POINT_RADIUS, pix_point.y - POINT_RADIUS);

    wnd.draw(point);
}

