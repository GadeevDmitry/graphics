#ifndef WIDGET_PROXY
#define WIDGET_PROXY

#include "widget.h"
#include "event/eventable_proxy.h"
#include "plugin/standart/WidgetI.h"

using plugin::EventProcessableI;
using plugin::WidgetI;

//==================================================================================================

class widget_proxy_t: public eventable_proxy
{
// static
public:
    static void inline widget_proxy_dtor         (void *widget_proxy_object);
    static void inline widget_proxy_dtor_internal(void *widget_proxy_object);

// member functions
public:
    explicit inline  widget_proxy_t(widget_t *internal);
    explicit inline  widget_proxy_t(WidgetI  *external);
             inline ~widget_proxy_t();

    void move          (const vec2d &offset)    const;
    void render        (render_texture_t &rend) const;
    bool update_struct ()                       const;
    void recalc_regions()                       const;

    void set_status(widget_t::WIDGET_STATUS_TYPE status) const;
    widget_t::WIDGET_STATUS_TYPE get_status()            const;

// member data
public:
    union
    {
        widget_t *internal;
        WidgetI  *external;
    };
};

//--------------------------------------------------------------------------------------------------

inline widget_proxy_t::widget_proxy_t(widget_t *internal_):
eventable_proxy((eventable *) internal_),
internal       (              internal_)
{}

//--------------------------------------------------------------------------------------------------

inline widget_proxy_t::widget_proxy_t(WidgetI *external_):
eventable_proxy((EventProcessableI *) external_),
external       (                      external_)
{}

//--------------------------------------------------------------------------------------------------

inline widget_proxy_t::~widget_proxy_t()
{
    if (!is_internal) delete external;
}

//--------------------------------------------------------------------------------------------------

inline void widget_proxy_t::widget_proxy_dtor(void *widget_proxy_object)
{
    ((widget_proxy_t *) widget_proxy_object)->~widget_proxy_t();
}

//--------------------------------------------------------------------------------------------------

inline void widget_proxy_t::widget_proxy_dtor_internal(void *widget_proxy_object)
{
    widget_proxy_t *widget_proxy = (widget_proxy_t *) widget_proxy_object;
    if (widget_proxy->is_internal) delete widget_proxy->internal;

    widget_proxy->~widget_proxy_t();
}

#endif // WIDGET_PROXY
