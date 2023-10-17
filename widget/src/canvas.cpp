#include <stdio.h>
#include "canvas.h"
#include "tool_manager.h"
#include "log.h"

//==================================================================================================

bool canvas_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == nullptr || active == (widget_t *) this, false);

    LOG_TAB_MESSAGE("CANVAS_T::ON_MOUSE_PRESS\n");
    LOG_TAB_MESSAGE("TOOL_MANAGER = %p\n", tool_manager);
    LOG_TAB_MESSAGE("REGION = {%lg, %lg} -> {%lg, %lg}\n",
                    visible.region.ld_corner.x,
                    visible.region.ld_corner.y,
                    visible.region.ru_corner.x,
                    visible.region.ru_corner.y);
    LOG_TAB++;

    const mouse_context_t &context = get_mouse_context();
    if (!visible.region.is_point_inside(context.pos))
    {
        LOG_TAB_ERROR_MESSAGE("MISSED", "\n");
        return false;
    }

    tool_manager->paint_on_mouse_press(*this, btn);
    active = (widget_t *) this;
    status = WIDGET_UPDATED;
    update_ancestral_status(WIDGET_UPDATED);

    LOG_TAB--;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool canvas_t::on_mouse_release(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == (widget_t *) this, false);

    LOG_TAB_MESSAGE("CANVAS_T::ON_MOUSE_RELEASE\n");
    LOG_TAB_MESSAGE("TOOL_MANAGER = %p\n", tool_manager);
    LOG_TAB++;

    tool_manager->paint_on_mouse_release(*this, btn);
    active = nullptr;
    status = WIDGET_UPDATED;
    update_ancestral_status(WIDGET_UPDATED);

    LOG_TAB--;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool canvas_t::on_mouse_move(const vec2d &off)
{
    LOG_VERIFY(active == (widget_t *) this, false);

    LOG_TAB_MESSAGE("CANVAS_T::ON_MOUSE_MOVE\n");
    LOG_TAB_MESSAGE("TOOL_MANAGER = %p\n", tool_manager);
    LOG_TAB++;

    tool_manager->paint_on_mouse_move(*this, off);
    status = WIDGET_UPDATED;
    update_ancestral_status(WIDGET_UPDATED);

    LOG_TAB--;
    return true;
}

//--------------------------------------------------------------------------------------------------

void canvas_t::render(render_texture_t &wnd)
{
    perm.display();
    temp.display();

    LOG_TAB_MESSAGE("CANVAS_T::RENDER\n");

    wnd.draw_texture(perm.get_texture(), visible.region.ld_corner, visible.region.get_size());
    wnd.draw_texture(temp.get_texture(), visible.region.ld_corner, visible.region.get_size());
}
