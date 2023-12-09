#include <stdio.h>
#include "russia_filter.h"

//==================================================================================================

void russia_filter_t::pixel_blending(plugin::Color &pixel, const color_t &background_color)
{
    color_t pixel_color = pixel.get_host_color();

    pixel_color.r = pixel_color.r * (1.0 - background_color.a) + background_color.r * background_color.a;
    pixel_color.g = pixel_color.g * (1.0 - background_color.a) + background_color.g * background_color.a;
    pixel_color.b = pixel_color.b * (1.0 - background_color.a) + background_color.b * background_color.a;

    pixel_color.r = std::min(pixel_color.r, 1.0);
    pixel_color.g = std::min(pixel_color.g, 1.0);
    pixel_color.b = std::min(pixel_color.b, 1.0);

    pixel = plugin::Color(pixel_color);
}

//--------------------------------------------------------------------------------------------------

void russia_filter_t::apply(RenderTargetI *perm)
{
    plugin::Texture *perm_texture = perm->get_texture();

    plugin::Color *perm_texture_pixels = perm_texture->pixels;
    unsigned y = 0;

    for (              ; 3*y < perm_texture->height; ++y) {
    for (unsigned x = 0; x   < perm_texture->width ; ++x)
        {
            pixel_blending(*perm_texture_pixels, color_t(1.0, 1.0, 1.0, power / 255.0));
            ++perm_texture_pixels;
        }
    }

    for (              ; 3*y < 2*perm_texture->height; ++y) {
    for (unsigned x = 0; x   <   perm_texture->width ; ++x)
        {
            pixel_blending(*perm_texture_pixels, color_t(0.0, 0.0, 1.0, power / 255.0));
            ++perm_texture_pixels;
        }
    }

    for (              ; y < perm_texture->height; ++y) {
    for (unsigned x = 0; x < perm_texture->width ; ++x)
        {
            pixel_blending(*perm_texture_pixels, color_t(1.0, 0.0, 0.0, power / 255.0));
            ++perm_texture_pixels;
        }
    }

    perm->draw_texture(
        vec2d(0, 0), vec2d((double) perm_texture->width, (double) perm_texture->height), perm_texture);
    delete perm_texture;
}
