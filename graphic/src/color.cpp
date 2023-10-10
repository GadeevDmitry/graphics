#include <stdio.h>
#include "color.h"
#include "algorithm.h"

//==================================================================================================

const color_t color_t::White  = color_t(1, 1, 1);
const color_t color_t::Black  = color_t(0, 0, 0);
const color_t color_t::Red    = color_t(1, 0, 0);
const color_t color_t::Green  = color_t(0, 1, 0);
const color_t color_t::Blue   = color_t(0, 0, 1);
const color_t color_t::Orange = color_t(1, 0.55, 0);

//==================================================================================================

sf::Color color_t::get_sfml_color() const
{
    return sf::Color((sf::Uint8) ((dblcmp(r, 1) > 0) ? 255 : 255 * r),
                     (sf::Uint8) ((dblcmp(g, 1) > 0) ? 255 : 255 * g),
                     (sf::Uint8) ((dblcmp(b, 1) > 0) ? 255 : 255 * b));
}

//--------------------------------------------------------------------------------------------------

color_t color_t::get_rand_color()
{
    double r = (double) (abs(rand()) % 255) / 255.0;
    double g = (double) (abs(rand()) % 255) / 255.0;
    double b = (double) (abs(rand()) % 255) / 255.0;

    return color_t(r, g, b);
}
