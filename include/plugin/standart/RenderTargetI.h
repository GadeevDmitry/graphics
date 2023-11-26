#ifndef PLUGIN_RENDER_TARGET_I_H
#define PLUGIN_RENDER_TARGET_I_H

#include "Color.h"
#include "geometry/vec2d.h"

//==================================================================================================

namespace plugin
{
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

#endif // PLUGIN_RENDER_TARGET_I_H
