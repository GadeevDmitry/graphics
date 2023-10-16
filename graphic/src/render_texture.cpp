#include <stdio.h>
#include "render_texture.h"
#include "log.h"

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

void render_texture_t::draw_texture(const texture_t &texture, const vec2d &pos, const vec2d &size, const clipping_region_t &reg)
{
    const list &regions = reg.get_areas();

    sf::Vector2u tex_size   = texture.data.getSize();
    rectangle_t  tex_region = reg.region;
    rectangle_t  tex_rect  (vec2d(pos.x, pos.y), vec2d(pos.x + size.x, pos.y + size.y));
    vec2d        tex_scale (size.x / tex_size.x, size.y / tex_size.y);

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        rectangle_t test_rect = tex_rect;

        if (intersect_rectangle_rectangle(test_rect, *cur))
        {
            sf::Sprite spr(texture.data);

            spr.setPosition((float) pos.x      , (float) pos.y);
            spr.setScale   ((float) tex_scale.x, (float) tex_scale.y);
            spr.setTextureRect(sf::IntRect((int) (test_rect.ld_corner.x - tex_region.ld_corner.x),
                                           (int) (test_rect.ld_corner.y - tex_region.ld_corner.y),
                                           (int) (test_rect.get_size().x / tex_scale.x),
                                           (int) (test_rect.get_size().y / tex_scale.y)));
            data.draw(spr);
        }
    }
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_region(const clipping_region_t &region)
{
    const list &areas = region.get_areas();

    rectangle_t *front = (rectangle_t *) list_front(&areas);
    rectangle_t *fict  = (rectangle_t *) list_fict (&areas);

    for (rectangle_t *cnt = front; cnt != fict;
         cnt = (rectangle_t *) list_next(cnt))
    {
        color_t rand = color_t::get_rand_color();
        draw_filled_rectangle(*cnt, color_t::Black, rand);
    }
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

void render_texture_t::draw_vec2d(const segment_t &abs, const color_t &col, const clipping_region_t &reg)
{
    vec2d reverse = abs.endpoint_1 - abs.endpoint_2;
    vec2d norm    = reverse.get_normal() / 3;

    vec2d fst_arr = (reverse + norm).get_normalization(VEC_ARROW_LEN);
    vec2d sec_arr = (reverse - norm).get_normalization(VEC_ARROW_LEN);

    draw_line(abs, col, reg);
    draw_line(segment_t(abs.endpoint_2, fst_arr.x, fst_arr.y), col, reg);
    draw_line(segment_t(abs.endpoint_2, sec_arr.x, sec_arr.y), col, reg);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_line(const segment_t &abs, const color_t &col, const clipping_region_t &reg)
{
    const list &regions = reg.get_areas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        segment_t test_segment = abs;
        if (intersect_line_rectangle(test_segment, *cur))
            draw_line(test_segment, col);
    }
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_segment(const segment_t &abs, const color_t &col, const clipping_region_t &reg)
{
    draw_line (abs           , col, reg);
    draw_point(abs.endpoint_1, col, reg);
    draw_point(abs.endpoint_2, col, reg);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_point(const vec2d &abs, const color_t &col, const clipping_region_t &reg)
{
    const list &regions = reg.get_areas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur->is_point_inside(abs))
        {
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

void render_texture_t::draw_hollow_rectangle(const rectangle_t &abs, const color_t &outline_col, const clipping_region_t &reg)
{
    const list &regions = reg.get_areas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        if (cur)
        {
            rectangle_t draw_zone = abs;
            if (intersect_rectangle_rectangle(draw_zone, *cur))
                draw_hollow_rectangle(draw_zone, outline_col);
        }
    }
}

//--------------------------------------------------------------------------------------------------
/*
void render_texture_t::draw_filled_rectangle(const rectangle_t &abs, const color_t &outline_col, const color_t &fill_col, const clipping_region_t &reg)
{
    const list &regions = reg.get_areas();

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
*/
//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_filled_rectangle(const rectangle_t &abs, const color_t &fill_col, const clipping_region_t &reg)
{
    const list &regions = reg.get_areas();

    rectangle_t *front = (rectangle_t *) list_front(&regions);
    rectangle_t *fict  = (rectangle_t *) list_fict (&regions);

    for (rectangle_t *cur = front; cur != fict;
         cur = (rectangle_t *) list_next(cur))
    {
        rectangle_t draw_zone = abs;
        if (intersect_rectangle_rectangle(draw_zone, *cur))
            draw_filled_rectangle(draw_zone, fill_col);
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

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_filled_circle(const circle_t &abs, const color_t &outline_col, const color_t &fill_col, const clipping_region_t &reg)
{
    sf::CircleShape sfml_circle = sf::CircleShape((float) abs.radius);

    vec2d circle_pos = vec2d(abs.center.x - abs.radius, abs.center.y - abs.radius);
    vec2d txt_size   = vec2d(data.getSize().x, data.getSize().y);

    sfml_circle.setPosition    ((float) circle_pos.x, (float) circle_pos.y);
    sfml_circle.setFillColor   (fill_col.get_sfml_color());
    sfml_circle.setOutlineColor(outline_col.get_sfml_color());

    sf::RenderTexture tmp_render_texture;
    tmp_render_texture.create ((unsigned) txt_size.x, (unsigned) txt_size.y);
    tmp_render_texture.draw   (sfml_circle);
    tmp_render_texture.display();

    texture_t circle_texture = texture_t(tmp_render_texture.getTexture());
    draw_texture(circle_texture, circle_pos, vec2d(abs.radius * 2, abs.radius * 2), reg);
}

//--------------------------------------------------------------------------------------------------

void render_texture_t::draw_filled_circle(const circle_t &abs, const color_t &fill_col, const clipping_region_t &reg)
{
    sf::CircleShape sfml_circle = sf::CircleShape((float) abs.radius);

    vec2d circle_pos = vec2d(abs.center.x - abs.radius, abs.center.y - abs.radius);
    vec2d txt_size   = vec2d(data.getSize().x, data.getSize().y);

    sfml_circle.setPosition ((float) circle_pos.x, (float) circle_pos.y);
    sfml_circle.setFillColor(fill_col.get_sfml_color());

    sf::RenderTexture tmp_render_texture;
    tmp_render_texture.create ((unsigned) txt_size.x, (unsigned) txt_size.y);
    tmp_render_texture.draw   (sfml_circle);
    tmp_render_texture.display();

    texture_t circle_texture = texture_t(tmp_render_texture.getTexture());
    draw_texture(circle_texture, circle_pos, vec2d(abs.radius * 2, abs.radius * 2), reg);
}
