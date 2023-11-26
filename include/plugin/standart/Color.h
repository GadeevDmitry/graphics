#ifndef PLUGIN_COLOR_H
#define PLUGIN_COLOR_H

#include <cinttypes>
#include "graphic/color.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

namespace plugin
{
    struct Color
    {
    // static
    public:
        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Orange;
        static const Color Transparent;

    // member functions
    public:
                 inline Color();
        explicit inline Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        color_t   inline get_host_color() const;
        sf::Color inline get_sfml_color() const;

    // member data
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    //--------------------------------------------------------------------------------------------------

    inline Color::Color():
    r(0),
    g(0),
    b(0),
    a(0)
    {}

    //--------------------------------------------------------------------------------------------------

    inline Color::Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_):
    r(r_),
    g(g_),
    b(b_),
    a(a_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline color_t Color::get_host_color() const
    {
        return color_t(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
    }

    //--------------------------------------------------------------------------------------------------

    inline sf::Color Color::get_sfml_color() const
    {
        return sf::Color((sf::Uint8) r, (sf::Uint8) g, (sf::Uint8) b, (sf::Uint8) a);
    }
};

#endif // PLUGIN_COLOR_H
