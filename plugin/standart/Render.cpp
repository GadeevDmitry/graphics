#include <stdio.h>
#include "standart/Render.h"

//==================================================================================================

namespace plugin
{
    const Color Color::White        ( 255, 255, 255, 255);
    const Color Color::Black        ( 0  , 0  , 0  , 255);
    const Color Color::Red          ( 0  , 0  , 0  , 255);
    const Color Color::Green        ( 0  , 255, 0  , 255);
    const Color Color::Blue         ( 0  , 0  , 255, 255);
    const Color Color::Orange       ( 255, 140, 0  , 255);
    const Color Color::Transparent  ( 0  , 0  , 0  , 0  );

    //==================================================================================================

    Color::Color(const color_t &color):
    r((uint8_t) std::min(255.0 * color.r, 255.0)),
    g((uint8_t) std::min(255.0 * color.g, 255.0)),
    b((uint8_t) std::min(255.0 * color.b, 255.0)),
    a((uint8_t) std::min(255.0 * color.a, 255.0))
    {}
}
