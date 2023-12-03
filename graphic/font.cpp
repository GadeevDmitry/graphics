#include <stdio.h>
#include "font.h"

//==================================================================================================

const char *font_t::FONTS_FILES[] =
{
    "assets/fonts/edu_qld.ttf",
    "assets/fonts/red_seven.otf",
    "assets/fonts/tupo_vyaz.ttf"
};

font_t font_t::FONTS[sizeof(font_t::FONTS_FILES) / sizeof(char *)] = {};

//==================================================================================================

void font_t::load_fonts()
{
    for (size_t i = 0; i * sizeof(char *) < sizeof(FONTS_FILES); ++i)
    {
        FONTS[i].load_from_file(FONTS_FILES[i]);
    }
};

//--------------------------------------------------------------------------------------------------

const font_t &font_t::get_font_by_name(const FONT_NAME_TYPE &name)
{
    if (name <= FONT_NAME_TYPE_UNKNOWN)
    {
        LOG_ERROR("undefined font name: %d\n", name);
        return FONTS[FONT_NAME_TYPE_UNKNOWN + 1];
    }

    if (name >= FONT_NAME_TYPE_COUNT)
    {
        LOG_ERROR("undefined font name: %d\n", name);
        return FONTS[FONT_NAME_TYPE_COUNT - 1];
    }

    return FONTS[name];
}

//--------------------------------------------------------------------------------------------------

unsigned font_t::get_char_size(const char requested, const size_t char_size) const
{
    if (requested >= 'A' && requested <= 'Z') return (unsigned) data.getGlyph(0x41 + requested - 'A', char_size, false).advance;
    if (requested >= 'a' && requested <= 'z') return (unsigned) data.getGlyph(0x61 + requested - 'a', char_size, false).advance;
    if (requested >= '0' && requested <= '9') return (unsigned) data.getGlyph(0x30 + requested - '0', char_size, false).advance;
    if (requested == '.')                     return (unsigned) data.getGlyph(0x2E                  , char_size, false).advance;

    return 0;
}
