#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"
#include "geometry/vec2d.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class render_texture_t;

class texture_t
{
// member functions
public:
             inline texture_t();
    explicit inline texture_t(const sf::Texture &data);
    explicit inline texture_t(const image_t &image);
    explicit inline texture_t(const char *filename);
    explicit inline texture_t(const unsigned width, const unsigned height);

    bool              inline  load_from_image (const image_t &image);
    bool              inline  load_from_file  (const char *filename);
    bool              inline  create          (const unsigned width, const unsigned height);

    vec2d             inline  get_size        () const;
    image_t           inline  get_image       () const;
    const sf::Texture inline &get_sfml_texture() const;

// member data
private:
    sf::Texture data;

// friends
    friend render_texture_t;
};

//--------------------------------------------------------------------------------------------------

inline texture_t::texture_t():
data()
{}

//--------------------------------------------------------------------------------------------------

inline texture_t::texture_t(const sf::Texture &data_):
data(data_)
{}

//--------------------------------------------------------------------------------------------------

inline texture_t::texture_t(const image_t &image):
data()
{
    data.loadFromImage(image.get_sfml_image());
}

//--------------------------------------------------------------------------------------------------

inline texture_t::texture_t(const char *filename_):
data()
{
    data.loadFromFile(filename_);
}

//--------------------------------------------------------------------------------------------------

inline texture_t::texture_t(const unsigned width_, const unsigned height_):
data()
{
    data.create(width_, height_);
}

//--------------------------------------------------------------------------------------------------

inline bool texture_t::load_from_image(const image_t &image)
{
    return data.loadFromImage(image.get_sfml_image());
}

//--------------------------------------------------------------------------------------------------

inline bool texture_t::load_from_file(const char *filename)
{
    return data.loadFromFile(filename);
}

//--------------------------------------------------------------------------------------------------

inline bool texture_t::create(const unsigned width, const unsigned height)
{
    return data.create(width, height);
}

//--------------------------------------------------------------------------------------------------

inline vec2d texture_t::get_size() const
{
    return vec2d((double) data.getSize().x, (double) data.getSize().y);
}

//--------------------------------------------------------------------------------------------------

inline image_t texture_t::get_image() const
{
    return image_t(data.copyToImage());
}

//--------------------------------------------------------------------------------------------------

inline const sf::Texture &texture_t::get_sfml_texture() const
{
    return data;
}

#endif // TEXTURE_H
