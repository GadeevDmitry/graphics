#ifndef PLUGIN_RENDER_H
#define PLUGIN_RENDER_H

#include "graphic/color.h"
#include "geometry/vec2d.h"

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
        explicit        Color(const color_t &color);

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

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    struct Texture
    {
    // member functions
    public:
        explicit inline Texture(uint64_t height, uint64_t width, Color *pixels);

    // member data
    public:
        uint64_t height;
        uint64_t width;
        Color   *pixels;
    };

    //--------------------------------------------------------------------------------------------------

    inline Texture::Texture(uint64_t height_, uint64_t width_, Color *pixels_):
    height(height_),
    width (width_),
    pixels(pixels_)
    {}

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    struct RenderTargetI
    {
    // virtual
    public:
        virtual void     set_pixel   (vec2d pos   ,               Color color) = 0;
        virtual void     draw_line   (vec2d point1, vec2d point2, Color color) = 0;
        virtual void     draw_rect   (vec2d pos   , vec2d size  , Color color) = 0;
        virtual void     draw_ellipse(vec2d pos   , vec2d size  , Color color) = 0;
        virtual void     draw_texture(vec2d pos   , vec2d size  , const Texture *texture) = 0;
        virtual void     draw_text   (vec2d pos   , const char *content, uint16_t char_size, Color color) = 0;

        virtual Texture *get_texture () = 0;

        virtual void     display     () = 0;
        virtual void     clear       () = 0;
    };
};

#endif // PLUGIN_RENDER_H
