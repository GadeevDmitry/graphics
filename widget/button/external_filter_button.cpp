#include <stdio.h>
#include "button/external_filter_button.h"

//==================================================================================================

bool external_filter_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) context;
    (void) btn;

    external_filter_button_t *filter_button = (external_filter_button_t *) handle;
    if (filter_button->filter != nullptr)
    {
        filter_manager.set_filter(filter_button->filter);

        plugin::Array<const char *> filter_param_names = filter_button->filter->get_param_names();
        if (filter_param_names.size != 0)
        {
            filter_param_window_t *filter_param_window = new filter_param_window_t(
                event_manager, filter_param_window_root.enclosing, "Settings", filter_button->filter);

            filter_param_window->status = widget_t::WIDGET_ACTIVATED;
            filter_param_window_root.register_subwidget(widget_proxy_t(filter_param_window));
        }
    }

    filter_button->status = widget_t::WIDGET_ACTIVATED;
    filter_button->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

external_filter_button_t::external_filter_button_t(external_filter_button_controller_t &controller_, const char *filter_name, FilterI *filter_):
label_button_t(controller_, filter_name, 20),
filter        (filter_)
{}

//--------------------------------------------------------------------------------------------------

external_filter_button_t::external_filter_button_t(external_filter_button_controller_t &controller_, const rectangle_t &enclosing_, const char *filter_name, FilterI *filter_):
label_button_t(controller_, enclosing_, filter_name, 20),
filter        (filter_)
{}
