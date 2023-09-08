#include <stdio.h>
#include <draw.h>

static const unsigned VEC_ARROW_LEN = 20;
static const unsigned POINT_RADIUS  = 3;

//==================================================================================================

void draw_vec(const vec &vec_beg, const vec &vec_main, const coord_system &sys,
              sf::RenderWindow &wnd, const sf::Color col)
{
    draw_pixel_vec(vec(sys.x_0, sys.y_0) + sys.get_pixel_from_vec(vec_beg),
                                           sys.get_pixel_from_vec(vec_main), wnd, col);
}

void draw_line(const vec &vec_beg, const vec &vec_main, const coord_system &sys,
               sf::RenderWindow &wnd, const sf::Color col)
{
    draw_pixel_line(sys.get_pixel_from_vec(vec_beg),
                    sys.get_pixel_from_vec(vec_main), wnd, col);
}

void draw_coord_sys(const coord_system &sys, sf::RenderWindow &wnd, const sf::Color col)
{
    sf::Vector2u wnd_size = wnd.getSize();
    double wnd_x = wnd_size.x;
    double wnd_y = wnd_size.y;

    draw_pixel_vec(vec(0, sys.y_0)    , vec(wnd_x, 0) , wnd, col);
    draw_pixel_vec(vec(sys.x_0, wnd_y), vec(0, -wnd_y), wnd, col);

    for (double pix_x = sys.x_0; pix_x > 0    ; pix_x -= sys.x_1_len) draw_pixel_point(vec(pix_x, sys.y_0), wnd, col);
    for (double pix_x = sys.x_0; pix_x < wnd_x; pix_x += sys.x_1_len) draw_pixel_point(vec(pix_x, sys.y_0), wnd, col);

    for (double pix_y = sys.y_0; pix_y > 0    ; pix_y -= sys.y_1_len) draw_pixel_point(vec(sys.x_0, pix_y), wnd, col);
    for (double pix_y = sys.y_0; pix_y < wnd_y; pix_y += sys.y_1_len) draw_pixel_point(vec(sys.x_0, pix_y), wnd, col);
}

void draw_pixel_vec(const vec &pix_beg, const vec &pix_main, sf::RenderWindow &wnd, sf::Color col)
{
    vec pix_end     = pix_beg + pix_main;
    vec pix_reverse = -pix_main;
    vec pix_norm    = !pix_reverse / 3;

    vec fst_arr = (pix_reverse + pix_norm) | VEC_ARROW_LEN;
    vec sec_arr = (pix_reverse - pix_norm) | VEC_ARROW_LEN;

    draw_pixel_line(pix_beg, pix_main, wnd, col);
    draw_pixel_line(pix_end, fst_arr , wnd, col);
    draw_pixel_line(pix_end, sec_arr , wnd, col);
}

void draw_pixel_line(const vec &pix_beg, const vec &pix_main, sf::RenderWindow &wnd, sf::Color col)
{
    vec pix_end = pix_beg + pix_main;
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(pix_beg.x, pix_beg.y), col),
                         sf::Vertex(sf::Vector2f(pix_end.x, pix_end.y), col)};

    wnd.draw(line, 2, sf::Lines);
}

void draw_pixel_point(const vec &pix_point, sf::RenderWindow &wnd, const sf::Color col)
{
    sf::CircleShape point;
    point.setRadius(POINT_RADIUS);
    point.setFillColor(col);
    point.setPosition(pix_point.x - POINT_RADIUS, pix_point.y - POINT_RADIUS);

    wnd.draw(point);
}

