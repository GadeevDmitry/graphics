#ifndef FONT_H
#define FONT_H

#include "geometry/vec2d.h"
#include "data_structs/include/log.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class render_texture_t;

class font_t
{
// types
public:
    enum FONT_NAME_TYPE
    {
        FONT_NAME_TYPE_UNKNOWN = -1,

        EDU_QLD,
        RED_SEVEN,
        TUPO_VYAZ,

        FONT_NAME_TYPE_COUNT
    };

// static
public:
    static void          load_fonts      ();
    static const font_t &get_font_by_name(const FONT_NAME_TYPE &name);
private:
    static font_t      FONTS[];
    static const char *FONTS_FILES[];

// member functions
public:
             inline font_t();
    explicit inline font_t(const FONT_NAME_TYPE &font_name);
    explicit inline font_t(const sf::Font &data);
    explicit inline font_t(const char *filename);

    bool           inline  load_from_file(const char *filename);
    const sf::Font inline &get_sfml_font () const;
    unsigned               get_char_size (const char requested, const size_t char_size) const;

// member data
private:
    sf::Font data;

// friends
    friend render_texture_t;
};

//--------------------------------------------------------------------------------------------------

inline font_t::font_t():
data()
{}

//--------------------------------------------------------------------------------------------------

inline font_t::font_t(const FONT_NAME_TYPE &font_name):
data()
{
    LOG_VERIFY(font_name > FONT_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(font_name < FONT_NAME_TYPE_COUNT  , ;);
    data = FONTS[font_name].data;
}

//--------------------------------------------------------------------------------------------------

inline font_t::font_t(const sf::Font &data_):
data(data_)
{}

//--------------------------------------------------------------------------------------------------

inline font_t::font_t(const char *filename):
data()
{
    data.loadFromFile(filename);
}

//--------------------------------------------------------------------------------------------------

inline bool font_t::load_from_file(const char *filename)
{
    return data.loadFromFile(filename);
}

//--------------------------------------------------------------------------------------------------

inline const sf::Font &font_t::get_sfml_font() const
{
    return data;
}

#endif // FONT_H
