#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include "geometry/vec2d.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class image_t
{
// member functions
public:
             inline image_t();
    explicit inline image_t(const sf::Image &data);
    explicit inline image_t(const unsigned width, const unsigned height);
    explicit inline image_t(const unsigned width, const unsigned height, const char *pixels);
    explicit inline image_t(const char *filename);

    void    inline  create         (const unsigned width, const unsigned height);
    void    inline  create         (const unsigned width, const unsigned height, const char *pixels);
    bool    inline  load_from_file (const char *filename);

    vec2d   inline  get_size       () const;
    char    inline *get_pixels     () const;
    color_t inline  get_pixel_color(const unsigned x, const unsigned y) const;
    void    inline  set_pixel_color(const unsigned x, const unsigned y, const color_t &color);

    const sf::Image inline &get_sfml_image() const;

// member data
private:
    sf::Image data;
};

//--------------------------------------------------------------------------------------------------

inline image_t::image_t():
data()
{}

//--------------------------------------------------------------------------------------------------

inline image_t::image_t(const sf::Image &data_):
data(data_)
{}

//--------------------------------------------------------------------------------------------------

inline image_t::image_t(const unsigned width, const unsigned height):
data()
{
    data.create(width, height);
}

//--------------------------------------------------------------------------------------------------

inline image_t::image_t(const unsigned width, const unsigned height, const char *pixels):
data()
{
    data.create(width, height, (const sf::Uint8 *) pixels);
}

//--------------------------------------------------------------------------------------------------

inline image_t::image_t(const char *filename):
data()
{
    data.loadFromFile(filename);
}

//--------------------------------------------------------------------------------------------------

inline void image_t::create(const unsigned width, const unsigned height)
{
    return data.create(width, height);
}

//--------------------------------------------------------------------------------------------------

inline void image_t::create(const unsigned width, const unsigned height, const char *pixels)
{
    return data.create(width, height, (const sf::Uint8 *) pixels);
}

//--------------------------------------------------------------------------------------------------

inline bool image_t::load_from_file(const char *filename)
{
    return data.loadFromFile(filename);
}

//--------------------------------------------------------------------------------------------------

inline vec2d image_t::get_size() const
{
    return vec2d((double) data.getSize().x, (double) data.getSize().y);
}

//--------------------------------------------------------------------------------------------------

inline char *image_t::get_pixels() const
{
    return (char *) data.getPixelsPtr();
}

//--------------------------------------------------------------------------------------------------

color_t image_t::get_pixel_color(const unsigned x, const unsigned y) const
{
    return color_t(data.getPixel(x, y));
}

//--------------------------------------------------------------------------------------------------

void image_t::set_pixel_color(const unsigned x, const unsigned y, const color_t &color)
{
    sf::Color sf_color = color.get_sfml_color();
    data.setPixel(x, y, sf_color);
}

//--------------------------------------------------------------------------------------------------

const sf::Image &image_t::get_sfml_image() const
{
    return data;
}

#endif // IMAGE_H
