#include <stdio.h>
#include "brightness_filter.h"

//==================================================================================================

void brightness_filter_t::apply(RenderTargetI *perm)
{
    plugin::Texture *perm_texture = perm->get_texture();

    plugin::Color *perm_texture_pixels = perm_texture->pixels;
    for (unsigned y = 0; y < perm_texture->height; ++y) {
    for (unsigned x = 0; x < perm_texture->width ; ++x)
        {
            perm_texture_pixels->r += brightness;
            perm_texture_pixels->g += brightness;
            perm_texture_pixels->b += brightness;

            ++perm_texture_pixels;
        }
    }

    perm->draw_texture(
        vec2d(0, 0), vec2d((double) perm_texture->width, (double) perm_texture->height), perm_texture);
}
