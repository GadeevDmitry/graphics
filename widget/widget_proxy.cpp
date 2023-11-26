#include <stdio.h>

#include "widget_proxy.h"
#include "plugin/host/HostRenderTargetI.h"

//==================================================================================================

void widget_proxy_t::move(const vec2d &offset) const
{
    if (is_internal) internal->move(offset);
    else             external->move(offset);
}

//--------------------------------------------------------------------------------------------------

void widget_proxy_t::render(render_texture_t &wnd) const
{
    if (is_internal) return internal->render(wnd);

    host::HostRenderTargetI temp(wnd);
    return external->render(&temp);
}

//--------------------------------------------------------------------------------------------------

bool widget_proxy_t::update_struct() const
{
    if (is_internal) return internal->update_struct();
    return true;
}

//--------------------------------------------------------------------------------------------------

void widget_proxy_t::recalc_regions() const
{
    if (is_internal) internal->recalc_regions();
    else             external->recalcRegion  ();
}

//--------------------------------------------------------------------------------------------------

void widget_proxy_t::set_status(widget_t::WIDGET_STATUS_TYPE status) const
{
    if (is_internal) internal->status = status;
    else
    {
        switch (status)
        {
            case widget_t::WIDGET_OPENED   : external->set_available(true );
            case widget_t::WIDGET_CLOSED   : external->set_available(false);
            case widget_t::WIDGET_ACTIVATED: break;

            default                        : LOG_ASSERT_VERBOSE(false, "undiefined \"widget_t::WIDGET_STATUS_TYPE\" value\n");
        }
    }
}

//--------------------------------------------------------------------------------------------------

widget_t::WIDGET_STATUS_TYPE widget_proxy_t::get_status() const
{
    if (is_internal) return internal->status;

    if (external->get_available()) return widget_t::WIDGET_OPENED;
    return widget_t::WIDGET_CLOSED;
}
