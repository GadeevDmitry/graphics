#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>
#include "vec2d.h"

//==================================================================================================

class render_texture_t;

class texture_t
{
private:
    sf::Texture data;

public:
    inline          texture_t();
    inline explicit texture_t(const sf::Texture &data_);
    inline explicit texture_t(const unsigned width_, const unsigned height_);
    inline explicit texture_t(const char *filename_);

    inline bool  create        (const unsigned width, const unsigned height);
    inline bool  load_from_file(const char *filename);
    inline vec2d get_size      () const;

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

inline texture_t::texture_t(const unsigned width_, const unsigned height_):
data()
{
    data.create(width_, height_);
}

//--------------------------------------------------------------------------------------------------

inline texture_t::texture_t(const char *filename_):
data()
{
    data.loadFromFile(filename_);
}

//--------------------------------------------------------------------------------------------------

inline bool texture_t::create(const unsigned width, const unsigned height)
{
    return data.create(width, height);
}

//--------------------------------------------------------------------------------------------------

inline bool texture_t::load_from_file(const char *filename)
{
    return data.loadFromFile(filename);
}

//--------------------------------------------------------------------------------------------------

inline vec2d  texture_t::get_size() const
{
    return vec2d((double) data.getSize().x, (double) data.getSize().y);
}

#endif // TEXTURE_H
