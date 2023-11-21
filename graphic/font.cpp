#include <stdio.h>
#include "graphic/font.h"

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
