#include <stdio.h>
#include "brightness_filter.h"

//==================================================================================================

struct ucolor_t
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

//==================================================================================================

void brightness_filter_t::apply(render_texture_t &perm)
{
    image_t perm_image = perm.get_image();

    vec2d     perm_image_size   = perm_image.get_size();
    ucolor_t *perm_image_pixels = (ucolor_t *) perm_image.get_pixels();

    for (unsigned y = 0; y < perm_image_size.y; ++y) {
    for (unsigned x = 0; x < perm_image_size.x; ++x)
        {
            perm_image_pixels->r += brightness;
            perm_image_pixels->g += brightness;
            perm_image_pixels->b += brightness;

            ++perm_image_pixels;
        }
    }

    texture_t result(perm_image);
    perm.draw_texture(result, vec2d(0, 0), result.get_size());
}
