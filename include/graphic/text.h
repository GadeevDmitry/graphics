#ifndef TEXT_H
#define TEXT_H

#include "font.h"
#include "color.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class text_t
{
// member functions
public:
             inline text_t();
             inline text_t(const text_t &text);
    explicit inline text_t(const font_t *font, const char *text,
                           const color_t &color = color_t::Black, const size_t &character_size = 30);

// member data
public:
    const font_t *font;
    const char   *text;
    color_t       color;
    size_t        character_size;
};

//--------------------------------------------------------------------------------------------------

inline text_t::text_t():
font          (nullptr),
text          (nullptr),
color         (color_t::Black),
character_size(30)
{}

//--------------------------------------------------------------------------------------------------

inline text_t::text_t(const text_t &text_):
font          (text_.font),
text          (text_.text),
color         (text_.color),
character_size(text_.character_size)
{}

//--------------------------------------------------------------------------------------------------

inline text_t::text_t(const font_t *font_, const char *text_, const color_t &color_, const size_t &character_size_):
font          (font_),
text          (text_),
color         (color_),
character_size(character_size_)
{}

#endif // TEXT_H
