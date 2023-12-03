#include <stdio.h>
#include "button/filter_button.h"

//==================================================================================================

bool filter_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    filter_button_t *filter_button = (filter_button_t *) handle;
    if (filter_button->filter != nullptr)
        filter_manager.set_filter(filter_button->filter);

    filter_button->status = widget_t::WIDGET_ACTIVATED;
    filter_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

filter_button_t::filter_button_t(widget_controller_t &controller_, const char *filter_name, FilterI *filter_):
label_button_t(controller_, filter_name, 20),
filter        (filter_)
{}

//--------------------------------------------------------------------------------------------------

filter_button_t::filter_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const char *filter_name, FilterI *filter_):
label_button_t(controller_, enclosing_, filter_name, 20),
filter        (filter_)
{}
