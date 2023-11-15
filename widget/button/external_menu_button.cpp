#include <stdio.h>
#include "button/external_menu_button.h"
#include "data_structs/include/log.h"

//==================================================================================================

bool external_menu_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;

    external_menu_button_t *external_menu_btn = (external_menu_button_t *) handle;

    external_menu_btn->is_menu_hidden =
        (external_menu_btn->is_menu_hidden) ? false : true;

    external_menu_btn->status = widget_t::WIDGET_ACTIVATED;
    external_menu_btn->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

external_menu_button_t::external_menu_button_t(widget_controller_t &controller_, menu_t &external_menu_, const char *btn_name):
label_button_t(controller_, btn_name, 20),
is_menu_hidden(true),
external_menu (external_menu_)
{
    external_menu.ancestor = this;
}

//--------------------------------------------------------------------------------------------------

external_menu_button_t::external_menu_button_t(widget_controller_t &controller_, menu_t &external_menu_, const rectangle_t &enclosing_, const char *btn_name):
label_button_t(controller_, enclosing_, btn_name, 20),
is_menu_hidden(true),
external_menu (external_menu_)
{
    external_menu.ancestor = this;
}

//--------------------------------------------------------------------------------------------------

void external_menu_button_t::dump() const
{
    dump_class_name();
    LOG_TAB_SERVICE_MESSAGE(" (address %p)\n{", "\n", this);
    LOG_TAB++;

    USUAL_FIELD_DUMP("status  ", "%d", status);
    USUAL_FIELD_DUMP("ancestor", "%p", ancestor);

    renderable::dump();

    LOG_TAB_SERVICE_MESSAGE("external_menu:\n{", "\n");
    LOG_TAB++;
    external_menu.dump();
    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n");

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n\n");
}

//--------------------------------------------------------------------------------------------------

bool external_menu_button_t::update_struct()
{
    LOG_ASSERT(status != WIDGET_CLOSED);

    if (is_menu_hidden) return false;

    switch (external_menu.status)
    {
        case WIDGET_OPENED   : return false;
        case WIDGET_CLOSED   : LOG_ASSERT_VERBOSE(false, "external_menu is closed\n"); return false;

        case WIDGET_ACTIVATED: LOG_ASSERT(is_menu_hidden == false);
                               external_menu.status = WIDGET_OPENED;
                               external_menu.update_struct();
                               return true;
        default: return false;
    }

    LOG_ASSERT_VERBOSE(false, "\"switch-case\" operator missing\n");
}

//--------------------------------------------------------------------------------------------------

void external_menu_button_t::recalc_regions()
{
    if (is_menu_hidden) return;

    external_menu.reset_regions ();
    external_menu.recalc_regions();

    own_visible   -= external_menu.sub_enclosing;
    sub_enclosing |= external_menu.sub_enclosing;
}

//--------------------------------------------------------------------------------------------------

bool external_menu_button_t::on_key_press(const key_context_t &context, const KEY_TYPE &key)
{
    LOG_VERIFY(active == nullptr, false);

    if (controller.on_key_press(this, context, key)) return true;
    if (!is_menu_hidden) return external_menu.on_key_press(context, key);

    return false;
}

//--------------------------------------------------------------------------------------------------

bool external_menu_button_t::on_mouse_press(const mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == nullptr, false);

    if (!sub_enclosing.is_point_inside(context.pos))
        return false;

    if (!enclosing.is_point_inside(context.pos))
    {
        LOG_ASSERT(is_menu_hidden == false);
        return external_menu.on_mouse_press(context, btn);
    }

    return controller.on_mouse_press(this, context, btn);
}
