#include <stdio.h>
#include "render_texture.h"

//==================================================================================================

static const unsigned VEC_ARROW_LEN = 20;
static const unsigned POINT_RADIUS  = 3;

//==================================================================================================

void render_texture_t::draw_texture(const texture_t &texture, const vec2d &pos, const vec2d &size)
{
    sf::Vector2u tex_size = texture.data.getSize();

    sf::Sprite spr(texture.data);
    spr.setPosition((float) pos.x, (float) pos.y);
    spr.setScale   ((float) (size.x / tex_size.x), (float) (size.y / tex_size.y));

    data.draw(spr);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_coord_sys(const coord_system &sys, const rectangle_t &area, const color_t &col)
{
    draw_vec2d(segment_t(vec2d(area.ld_corner.x, sys.center.y), vec2d(area.ru_corner.x, sys.center.y)), col);
    draw_vec2d(segment_t(vec2d(sys.center.x, area.ld_corner.y), vec2d(sys.center.x, area.ru_corner.y)), col);

    for (double x = sys.center.x; x > area.ld_corner.x; x -= sys.unit.x) draw_point(vec2d(x, sys.center.y), col);
    for (double x = sys.center.x; x < area.ru_corner.x; x += sys.unit.x) draw_point(vec2d(x, sys.center.y), col);

    for (double y = sys.center.y; y > area.ld_corner.y; y -= sys.unit.y) draw_point(vec2d(sys.center.x, y), col);
    for (double y = sys.center.y; y < area.ru_corner.y; y += sys.unit.y) draw_point(vec2d(sys.center.x, y), col);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_vec2d(const segment_t &abs, const color_t &col)
{
    vec2d reverse = abs.endpoint_1 - abs.endpoint_2;
    vec2d norm    = reverse.get_normal() / 3;

    vec2d fst_arr = (reverse + norm).get_normalization(VEC_ARROW_LEN);
    vec2d sec_arr = (reverse - norm).get_normalization(VEC_ARROW_LEN);

    draw_line(abs, col);
    draw_line(segment_t(abs.endpoint_2, fst_arr.x, fst_arr.y), col);
    draw_line(segment_t(abs.endpoint_2, sec_arr.x, sec_arr.y), col);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_line(const segment_t &abs, const color_t &col)
{
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f((float) abs.endpoint_1.x, (float) abs.endpoint_1.y), col.get_sfml_color()),
                         sf::Vertex(sf::Vector2f((float) abs.endpoint_2.x, (float) abs.endpoint_2.y), col.get_sfml_color())};

    data.draw(line, 2, sf::Lines);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_segment(const segment_t &abs, const color_t &col)
{
    draw_line (abs           , col);
    draw_point(abs.endpoint_1, col);
    draw_point(abs.endpoint_2, col);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_point(const vec2d &abs, const color_t &col)
{
    sf::CircleShape point;

    point.setRadius   (POINT_RADIUS);
    point.setFillColor(col.get_sfml_color());
    point.setPosition ((float) (abs.x - POINT_RADIUS), (float) (abs.y - POINT_RADIUS));

    data.draw(point);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_vec2d(const segment_t &abs, const color_t &col, const clipping_region_t &reg) {

}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_line(const segment_t &abs, const color_t &col, const clipping_region_t &reg) {

}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_segment(const segment_t &abs, const color_t &col, const clipping_region_t &reg) {

}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_point(const vec2d &abs, const color_t &col, const clipping_region_t &reg) {
    list regions = reg.getAreas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur->is_point_inside(abs)) {
            draw_point(abs, col);
            break;
        }
    }
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_hollow_rectangle(const rectangle_t &abs, const color_t &outline_col)
{
    sf::Color sfml_outline_col = outline_col.get_sfml_color();
    sf::Vertex lines[] = {sf::Vertex(sf::Vector2f((float) abs.ld_corner.x, (float) abs.ld_corner.y), sfml_outline_col),
                          sf::Vertex(sf::Vector2f((float) abs.ru_corner.x, (float) abs.ld_corner.y), sfml_outline_col),
                          sf::Vertex(sf::Vector2f((float) abs.ru_corner.x, (float) abs.ru_corner.y), sfml_outline_col),
                          sf::Vertex(sf::Vector2f((float) abs.ld_corner.x, (float) abs.ru_corner.y), sfml_outline_col),
                          sf::Vertex(sf::Vector2f((float) abs.ld_corner.x, (float) abs.ld_corner.y), sfml_outline_col)};

    data.draw(lines, 5, sf::LineStrip);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_filled_rectangle(const rectangle_t &abs, const color_t &outline_col, const color_t &fill_col)
{
    vec2d size = abs.ru_corner - abs.ld_corner;
    sf::RectangleShape rect(sf::Vector2f((float) size.x, (float) size.y));

    rect.setPosition    ((float) abs.ld_corner.x, (float) abs.ld_corner.y);
    rect.setOutlineColor(outline_col.get_sfml_color());
    rect.setFillColor   (   fill_col.get_sfml_color());

    data.draw(rect);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_hollow_rectangle(const rectangle_t &abs, const color_t &outline_col, const clipping_region_t &reg) {
    list regions = reg.getAreas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur) {
            rectangle_t draw_zone = abs;
            if (intersect_rectangle_rectangle(draw_zone, *cur)) {
                draw_hollow_rectangle(draw_zone, outline_col);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_filled_rectangle(const rectangle_t &abs, const color_t &outline_col, const color_t &fill_col, const clipping_region_t &reg) {
    list regions = reg.getAreas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur) {
            rectangle_t draw_zone = abs;
            if (intersect_rectangle_rectangle(draw_zone, *cur)) {
                draw_filled_rectangle(draw_zone, outline_col, fill_col);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_filled_rectangle(const rectangle_t &abs, const color_t &fill_col, const clipping_region_t &reg) {
    list regions = reg.getAreas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur) {
            rectangle_t draw_zone = abs;
            if (intersect_rectangle_rectangle(draw_zone, *cur)) {
                draw_filled_rectangle(draw_zone, fill_col);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_filled_circle(const circle_t &abs, const color_t &outline_col, const color_t &fill_col)
{
    sf::CircleShape circle((float) abs.radius);

    circle.setPosition    ((float) (abs.center.x - abs.radius), (float) (abs.center.y - abs.radius));
    circle.setOutlineColor(outline_col.get_sfml_color());
    circle.setFillColor   (   fill_col.get_sfml_color());

    data.draw(circle);
}
