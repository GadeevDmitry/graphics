#ifndef PLUGIN_HOST_RENDER_TARGET_I_H
#define PLUGIN_HOST_RENDER_TARGET_I_H

#include "plugin/standart/Render.h"
#include "graphic/render_texture.h"

//==================================================================================================

using plugin::Color;
using plugin::Texture;

namespace host
{
    class HostRenderTargetI: public plugin::RenderTargetI
    {
    // member functions
    public:
        explicit inline HostRenderTargetI(render_texture_t &render_texture);

    // virtual
    public:
        virtual void            set_pixel   (vec2d pos   ,               Color color)                            override;
        virtual void    inline  draw_line   (vec2d point1, vec2d point2, Color color)                            override;
        virtual void            draw_rect   (vec2d pos   , vec2d size  , Color color)                            override;
        virtual void            draw_ellipse(vec2d pos   , vec2d size  , Color color)                            override;
        virtual void            draw_texture(vec2d pos   , vec2d size  , const Texture *texture)                 override;
        virtual void            draw_text   (vec2d pos   , const char *content, uint16_t char_size, Color color) override;

        virtual Texture        *get_texture () override;

        virtual void    inline  display     () override;
        virtual void    inline  clear       () override;

    // member data
    private:
        render_texture_t &render_texture;
    };

    //--------------------------------------------------------------------------------------------------

    inline HostRenderTargetI::HostRenderTargetI(render_texture_t &render_texture_):
    render_texture(render_texture_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline void HostRenderTargetI::draw_line(vec2d point1, vec2d point2, Color color)
    {
        render_texture.draw_line(segment_t(point1, point2), color.get_host_color());
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostRenderTargetI::display()
    {
        render_texture.display();
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostRenderTargetI::clear()
    {
        render_texture.clear(color_t::Transparent);
    }
}

#endif // PLUGIN_HOST_RENDER_TARGET_I_H
