#include <stdio.h>
#include "widget.h"
#include "data_structs/include/log.h"

//==================================================================================================

widget_t *widget_t::active = nullptr;

//==================================================================================================

bool widget_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    widget_t::active = handle;
    handle->status = widget_t::WIDGET_ACTIVATED;
    handle->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool widget_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;

    widget_t::active = nullptr;
    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void widget_t::update_ancestral_status(WIDGET_STATUS_TYPE upd_status)
{
    for (widget_t *cur = ancestor; cur != nullptr; cur = cur->ancestor)
        cur->status = upd_status;
}

//--------------------------------------------------------------------------------------------------

void widget_t::dump() const
{
    LOG_TAB_SERVICE_MESSAGE("widget_t (address: %p)\n{", "\n", this);
    LOG_TAB++;

    USUAL_FIELD_DUMP("status  ", "%d", status);
    USUAL_FIELD_DUMP("ancestor", "%p", ancestor);

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");
}
