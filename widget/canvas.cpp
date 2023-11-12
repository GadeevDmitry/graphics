#include <stdio.h>
#include "canvas.h"
#include "tool/tool_manager.h"
#include "data_structs/include/log.h"

//==================================================================================================

bool canvas_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    canvas_t *canvas = (canvas_t *) handle;

    eventable::mouse_context_t local_context = context;
    local_context.pos -= canvas->enclosing.ld_corner;
    tool_manager.paint_on_mouse_press(canvas->perm, canvas->temp, local_context, btn);

    widget_t::active = handle;
    canvas->status = widget_t::WIDGET_ACTIVATED;
    canvas->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool canvas_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    canvas_t *canvas = (canvas_t *) handle;

    eventable::mouse_context_t local_context = context;
    local_context.pos -= canvas->enclosing.ld_corner;
    tool_manager.paint_on_mouse_release(canvas->perm, canvas->temp, local_context, btn);

    widget_t::active = nullptr;
    canvas->status = widget_t::WIDGET_ACTIVATED;
    canvas->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool canvas_controller_t::on_mouse_move(widget_t *handle, const eventable::mouse_context_t &context, const vec2d &off)
{
    canvas_t *canvas = (canvas_t *) handle;

    eventable::mouse_context_t local_context = context;
    local_context.pos -= canvas->enclosing.ld_corner;
    tool_manager.paint_on_mouse_move(canvas->perm, canvas->temp, local_context, off);

    canvas->status = widget_t::WIDGET_ACTIVATED;
    canvas->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void canvas_t::create_textures(const color_t &background)
{
    perm.create((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);
    temp.create((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);

    perm.clear(background);
    temp.clear(color_t::Transparent);
}

//--------------------------------------------------------------------------------------------------

void canvas_t::render(render_texture_t &wnd)
{
    perm.display();
    temp.display();

    wnd.draw_texture(perm.get_texture(), enclosing, own_visible);
    wnd.draw_texture(temp.get_texture(), enclosing, own_visible);
}
