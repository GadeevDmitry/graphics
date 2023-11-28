#ifndef TOOL_H
#define TOOL_H

#include "plugin/standart/Tool.h"
#include "event/eventable.h"
#include "graphic/render_texture.h"

//==================================================================================================

using plugin::RenderTargetI;
using plugin::MouseContext;
using plugin::Color;

class tool_t: public plugin::ToolI
{
// member functions
public:
            inline  tool_t();
    virtual inline ~tool_t() {}

// virtual
    virtual plugin::Array<const char *> inline get_param_names()                             override;
    virtual plugin::Array<double>       inline get_params     ()                             override;
    virtual void                        inline set_params     (plugin::Array<double> params) override;

    virtual const plugin::Texture inline *get_icon() override;
    virtual void inline deactivate(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color) override;

// member data
protected:
    vec2d start;
    vec2d last;
};

//--------------------------------------------------------------------------------------------------

tool_t::tool_t():
start(),
last ()
{}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<const char *> tool_t::get_param_names()
{
    return plugin::Array<const char *>(0, nullptr);
}

//--------------------------------------------------------------------------------------------------

inline plugin::Array<double> tool_t::get_params()
{
    return plugin::Array<double>(0, nullptr);
}

//--------------------------------------------------------------------------------------------------

inline void tool_t::set_params(plugin::Array<double> params)
{
    (void) params;
}

//--------------------------------------------------------------------------------------------------

inline const plugin::Texture *tool_t::get_icon()
{
    return nullptr;
}

//--------------------------------------------------------------------------------------------------

inline void tool_t::deactivate(RenderTargetI *perm, RenderTargetI *temp, MouseContext local_context, Color color)
{
    (void) perm;
    (void) temp;
    (void) local_context;
    (void) color;
}

#endif // TOOL_H
