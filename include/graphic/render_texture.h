#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "color.h"
#include "region.h"
#include "texture.h"
#include "geometry/intersect.h"
#include "geometry/shape_types.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class render_texture_t
{
// member functions
public:
             inline  render_texture_t();
    explicit inline  render_texture_t(const unsigned width, const unsigned height);
             inline ~render_texture_t() {}

    const sf::Texture inline &get_sfml_texture() const;
    texture_t         inline  get_texture     () const;

    bool inline create        (const unsigned width, const unsigned height);
    void inline clear         (const color_t &col = color_t::Black);
    void inline display       ();

    void        draw_texture  (const texture_t &texture, const vec2d &pos, const vec2d &size);
    void        draw_texture  (const texture_t &texture, const clipping_region_t &reg);

    void        draw_region   (const clipping_region_t &reg);

    void        draw_coord_sys(const coord_system &sys, const rectangle_t &area, const color_t &col);

    void inline draw_vec2d    (const segment_t    &rel, const coord_system &sys, const color_t &col);
    void inline draw_line     (const segment_t    &rel, const coord_system &sys, const color_t &col);
    void inline draw_segment  (const segment_t    &rel, const coord_system &sys, const color_t &col);
    void inline draw_point    (const vec2d        &rel, const coord_system &sys, const color_t &col);

    void        draw_vec2d    (const segment_t    &abs, const color_t &col);
    void        draw_line     (const segment_t    &abs, const color_t &col);
    void        draw_segment  (const segment_t    &abs, const color_t &col);
    void        draw_point    (const vec2d        &abs, const color_t &col);

    void        draw_vec2d    (const segment_t    &abs, const color_t &col, const clipping_region_t &reg);
    void        draw_line     (const segment_t    &abs, const color_t &col, const clipping_region_t &reg);
    void        draw_segment  (const segment_t    &abs, const color_t &col, const clipping_region_t &reg);
    void        draw_point    (const vec2d        &abs, const color_t &col, const clipping_region_t &reg);

    void        draw_rectangle(const rectangle_t  &abs, const color_t &fill_col, const color_t &out_col, const double out_thickness);
    void        draw_rectangle(                         const color_t &fill_col, const clipping_region_t &reg);

    void        draw_circle   (const circle_t     &abs, const color_t &fiil_col, const color_t &out_col, const double out_thickness, const vec2d &scale);
    void        draw_circle   (const circle_t     &abs, const color_t &fill_col, const clipping_region_t &reg, const vec2d &scale);

// member data
private:
    sf::RenderTexture data;
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

inline texture_t render_texture_t::get_texture() const
{
    return texture_t(get_sfml_texture());
}

//--------------------------------------------------------------------------------------------------

inline bool render_texture_t::create(const unsigned width, const unsigned height)
{
    return data.create(width, height);
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::clear(const color_t &col)
{
    data.clear(col.get_sfml_color());
}

//--------------------------------------------------------------------------------------------------

inline void render_texture_t::display()
{
    data.display();
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

#endif // RENDER_TEXTURE_H
