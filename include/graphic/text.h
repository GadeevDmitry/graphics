#ifndef TEXT_H
#define TEXT_H

#include "font.h"
#include "color.h"
#include "geometry/vec2d.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class text_t
{
// member functions
public:
             inline text_t();
             inline text_t(const text_t &text);
    explicit inline text_t(const font_t *font, const char *string,
                           const color_t &color = color_t::Black, const size_t &character_size = 30);

    vec2d inline get_string_size() const;

// member data
public:
    const font_t *font;
    const char   *string;
    color_t       color;
    size_t        character_size;
};

//--------------------------------------------------------------------------------------------------

inline text_t::text_t():
font          (nullptr),
string        (nullptr),
color         (color_t::Black),
character_size(30)
{}

//--------------------------------------------------------------------------------------------------

inline text_t::text_t(const text_t &text_):
font          (text_.font),
string        (text_.string),
color         (text_.color),
character_size(text_.character_size)
{}

//--------------------------------------------------------------------------------------------------

inline text_t::text_t(const font_t *font_, const char *string_, const color_t &color_, const size_t &character_size_):
font          (font_),
string        (string_),
color         (color_),
character_size(character_size_)
{}

//--------------------------------------------------------------------------------------------------

inline vec2d text_t::get_string_size() const
{
    return vec2d(
        sf::Text(string, font->get_sfml_font(), character_size).getLocalBounds().width,
        sf::Text(string, font->get_sfml_font(), character_size).getLocalBounds().height);
}

#endif // TEXT_H
