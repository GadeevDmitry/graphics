#include <stdio.h>

#include "host/HostRenderTargetI.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

namespace host
{
    void HostRenderTargetI::set_pixel(vec2d pos, Color color)
    {
        sf::Vertex sf_vertex(sf::Vector2f((float) pos.x, (float) pos.y), color.get_sfml_color());
        render_texture.data.draw(&sf_vertex, 1, sf::Points);
    }

    //--------------------------------------------------------------------------------------------------

    void HostRenderTargetI::draw_rect(vec2d pos, vec2d size, Color color)
    {
        render_texture.draw_rectangle(
            rectangle_t(pos, pos + size),
            color_t::Transparent,
            color.get_host_color(),
            1);
    }

    //--------------------------------------------------------------------------------------------------

    void HostRenderTargetI::draw_ellipse(vec2d pos, vec2d size, Color color)
    {
        double y_scale = (dblcmp(size.x, 0) == 0) ? 0 : size.y / size.x;
        double x_scale = (dblcmp(size.y, 0) == 0) ? 0 : size.x / size.y;

        vec2d center = pos + size / 2;
        if (size.x < size.y)
        {
            circle_t circle(center, size.x / 2);
            render_texture.draw_circle(circle, color_t::Transparent, color.get_host_color(), 1, vec2d(1, y_scale));
        }
        else
        {
            circle_t circle(center, size.y / 2);
            render_texture.draw_circle(circle, color_t::Transparent, color.get_host_color(), 1, vec2d(x_scale, 1));
        }
    }

    //--------------------------------------------------------------------------------------------------

    void HostRenderTargetI::draw_texture(vec2d pos, vec2d size, const Texture *texture)
    {
        image_t   temp_image  ((unsigned) size.x, (unsigned) size.y, (const char *) texture->pixels);
        texture_t temp_texture(temp_image);

        render_texture.draw_texture(temp_texture, pos, size);
    }

    //--------------------------------------------------------------------------------------------------

    void HostRenderTargetI::draw_text(vec2d pos, const char *content, uint16_t char_size, Color color)
    {
        text_t temp_text(
            &font_t::get_font_by_name(font_t::EDU_QLD),
            content,
            color.get_host_color(),
            char_size);

        render_texture.draw_text(temp_text, pos);
    }

    //--------------------------------------------------------------------------------------------------

    Texture *HostRenderTargetI::get_texture()
    {
        image_t temp_image = render_texture.get_image();
        return new Texture(
            (uint64_t) temp_image.get_size().x,
            (uint64_t) temp_image.get_size().y,
            (Color *)  temp_image.get_pixels());
    }
}
