#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "color.h"
#include "region.h"
#include "texture.h"
#include "intersect.h"
#include "shape_types.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class render_texture_t
{
private:
    sf::RenderTexture data;

public:
    inline          render_texture_t();
    inline explicit render_texture_t(const unsigned width_, const unsigned height_);
    inline         ~render_texture_t() {}

    inline const sf::Texture &get_sfml_texture() const;

    inline bool create               (const unsigned width, const unsigned height);
    inline void clear                ();

    void        draw_texture         (const texture_t &texture, const vec2d &pos, const vec2d &size);
    void        draw_texture         (const texture_t &texture, const vec2d &pos, const vec2d &size, const clipping_region_t &reg);

    void        draw_coord_sys       (const coord_system &sys, const rectangle_t &area, const color_t &col);

    inline void draw_vec2d           (const segment_t    &rel, const coord_system &sys, const color_t &col);
    inline void draw_line            (const segment_t    &rel, const coord_system &sys, const color_t &col);
    inline void draw_segment         (const segment_t    &rel, const coord_system &sys, const color_t &col);
    inline void draw_point           (const vec2d        &rel, const coord_system &sys, const color_t &col);

    void        draw_vec2d           (const segment_t    &abs, const color_t &col);
    void        draw_line            (const segment_t    &abs, const color_t &col);
    void        draw_segment         (const segment_t    &abs, const color_t &col);
    void        draw_point           (const vec2d        &abs, const color_t &col);

    void        draw_vec2d           (const segment_t    &abs, const color_t &col, const clipping_region_t &reg);
    void        draw_line            (const segment_t    &abs, const color_t &col, const clipping_region_t &reg);
    void        draw_segment         (const segment_t    &abs, const color_t &col, const clipping_region_t &reg);
    void        draw_point           (const vec2d        &abs, const color_t &col, const clipping_region_t &reg);

    void        draw_hollow_rectangle(const rectangle_t  &abs, const color_t &outline_col);
    void        draw_filled_rectangle(const rectangle_t  &abs, const color_t &outline_col, const color_t &fill_col);
    inline void draw_filled_rectangle(const rectangle_t  &abs, const color_t &   fill_col);

    void        draw_hollow_rectangle(const rectangle_t  &abs, const color_t &outline_col,                          const clipping_region_t &reg);
//  void        draw_filled_rectangle(const rectangle_t  &abs, const color_t &outline_col, const color_t &fill_col, const clipping_region_t &reg);
    void        draw_filled_rectangle(const rectangle_t  &abs, const color_t &fill_col,                             const clipping_region_t &reg);

    void        draw_filled_circle   (const circle_t     &abs, const color_t &outline_col, const color_t &fill_col);
    inline void draw_filled_circle   (const circle_t     &abs, const color_t &   fill_col);

    void        draw_filled_circle   (const circle_t     &abs, const color_t &outline_col, const color_t &fill_col, const clipping_region_t &reg);
    void        draw_filled_circle   (const circle_t     &abs, const color_t &   fill_col,                          const clipping_region_t &reg);
};

//==================================================================================================

inline render_texture_t::render_texture_t():
data()
{}

//--------------------------------------------------------------------------------------------------

inline render_texture_t::render_texture_t(const unsigned width_, const unsigned height_):
data()
{
    data.create(width_, height_);
}

//--------------------------------------------------------------------------------------------------

inline const sf::Texture &render_texture_t::get_sfml_texture() const
{
    return data.getTexture();
}

//--------------------------------------------------------------------------------------------------

inline bool render_texture_t::create(const unsigned width, const unsigned height)
{
    return data.create(width, height);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::clear()
{
    data.clear();
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_vec2d(const segment_t &rel, const coord_system &sys, const color_t &col)
{
    draw_vec2d(segment_t(sys.get_off_from_rel(rel.endpoint_1),
                         sys.get_off_from_rel(rel.endpoint_2)), col);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_line(const segment_t &rel, const coord_system &sys, const color_t &col)
{
    draw_line(segment_t(sys.get_off_from_rel(rel.endpoint_1),
                        sys.get_off_from_rel(rel.endpoint_2)), col);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_segment(const segment_t &rel, const coord_system &sys, const color_t &col)
{
    draw_segment(segment_t(sys.get_off_from_rel(rel.endpoint_1),
                           sys.get_off_from_rel(rel.endpoint_2)), col);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_point(const vec2d &rel, const coord_system &sys, const color_t &col)
{
    draw_point(sys.get_off_from_rel(rel), col);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_filled_rectangle(const rectangle_t &abs, const color_t &fill_col)
{
    return draw_filled_rectangle(abs, fill_col, fill_col);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::draw_filled_circle(const circle_t &abs, const color_t &fill_col)
{
    return draw_filled_circle(abs, fill_col, fill_col);
}

#endif // RENDER_TEXTURE_H
