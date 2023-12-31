#include <stdio.h>
#include "color.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

const color_t color_t::White        ( 1     , 1     , 1     , 1     );
const color_t color_t::Black        ( 0     , 0     , 0     , 1     );
const color_t color_t::Red          ( 1     , 0     , 0     , 1     );
const color_t color_t::Green        ( 0     , 1     , 0     , 1     );
const color_t color_t::Blue         ( 0     , 0     , 1     , 1     );
const color_t color_t::Orange       ( 1     , 0.55  , 0     , 1     );
const color_t color_t::Transparent  ( 0     , 0     , 0     , 0     );

//==================================================================================================

sf::Color color_t::get_sfml_color() const
{
    return sf::Color((sf::Uint8) ((dblcmp(r, 1) > 0) ? 255 : 255 * r),
                     (sf::Uint8) ((dblcmp(g, 1) > 0) ? 255 : 255 * g),
                     (sf::Uint8) ((dblcmp(b, 1) > 0) ? 255 : 255 * b),
                     (sf::Uint8) ((dblcmp(a, 1) > 0) ? 255 : 255 * a));
}

//--------------------------------------------------------------------------------------------------

void color_t::maximize_brightness()
{
    double fictional_k = 1000.0;

    double r_k = (dblcmp(r, 0) == 0) ? fictional_k : 255.0 / r;
    double g_k = (dblcmp(g, 0) == 0) ? fictional_k : 255.0 / g;
    double b_k = (dblcmp(b, 0) == 0) ? fictional_k : 255.0 / b;

    double min_k = std::min({r_k, g_k, b_k});

    r *= min_k;
    g *= min_k;
    b *= min_k;
}

//--------------------------------------------------------------------------------------------------

color_t color_t::get_rand_color()
{
    double r = (double) (abs(rand()) % 255) / 255.0;
    double g = (double) (abs(rand()) % 255) / 255.0;
    double b = (double) (abs(rand()) % 255) / 255.0;
//  double a = (double) (abs(rand()) % 255) / 255.0;

    return color_t(r, g, b, 1);
}
