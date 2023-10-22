#include <stdio.h>
#include "window.h"
#include "log.h"

//==================================================================================================

const color_t window_t::Light_theme  ( 0.871 , 0.871 , 0.871 );
const color_t window_t::Dark_theme   ( 0.243 , 0.243 , 0.259 );
const color_t window_t::Blue_theme   ( 0     , 0.478 , 0.800 );
const color_t window_t::Red_theme    ( 0.533 , 0     , 0     );

//==================================================================================================

static const double HEADER_MENU_HEIGHT = 50;

static const vec2d  TOOLBAR_SIZE    (250, 515);
static const vec2d  TOOLBAR_BTN_SIZE(100, 100);
static const size_t TOOLBAR_BTN_NUMS = 8;

static const vec2d  PALETTE_SIZE    (250, 515);
static const vec2d  PALETTE_BTN_SIZE(100, 100);
static const size_t PALETTE_BTN_NUMS = 6;

//==================================================================================================

window_t::window_t(const rectangle_t &region_, const color_t &color_):
widget_manager_t(nullptr, region_),
color           (color_),
header_menu     (button_t::button_delete)
{
    header_menu_create();
}

//--------------------------------------------------------------------------------------------------

void window_t::header_menu_create()
{
    vec2d wnd_size = visible.region.get_size();
    if (wnd_size.y < HEADER_MENU_HEIGHT)
    {
        LOG_ERROR("CAN'T CREATE WINDOW: height is too small for header menu (%lg < %lg)\n",
                  wnd_size.y, HEADER_MENU_HEIGHT);
        return;
    }

    rectangle_t header_menu_region(visible.region.ld_corner,
                                   visible.region.rd_corner() + vec2d(0, HEADER_MENU_HEIGHT));

    header_menu.set_region(header_menu_region);
    header_menu.set_funcs (nullptr, nullptr,
                           activate_by_mouse_click,
                           deactivate_by_mouse_click,
                           move_by_mouse_move);
    header_menu.set_args  (this);
    header_menu.color = color_t::White;

    header_menu_create_winapi_btn();

    register_subwidget(&header_menu);
}

//--------------------------------------------------------------------------------------------------

void window_t::header_menu_create_winapi_btn()
{
    rectangle_t header_region = header_menu.visible.region;
    vec2d       header_size   = header_region.get_size();

    texture_button_t *winapi = new texture_button_t(button_t::GREEN_WINAPI);

    vec2d  winapi_size  = winapi->texture.get_size();
    double winapi_scale = header_size.y / winapi_size.y;

    winapi_size = vec2d(winapi_size.x * winapi_scale, header_size.y);
    rectangle_t winapi_region(header_region.rd_corner() - vec2d(winapi_size.x, 0),
                              header_region.rd_corner() + vec2d(0, winapi_size.y));

    winapi->set_region(winapi_region);
    winapi->set_funcs(nullptr, nullptr, activate_by_mouse_click, close_by_mouse_click, nullptr);
    winapi->set_args (this);

    header_menu.register_button(winapi);
}

//--------------------------------------------------------------------------------------------------

bool window_t::on_mouse_press(const MOUSE_BUTTON_TYPE &btn)
{
    LOG_ASSERT(active == nullptr);

    const mouse_context_t &context = get_mouse_context();
    if (!visible.region.is_point_inside(context.pos))
        return false;

    LOG_TAB_MESSAGE("WINDOW_T::ON_MOUSE_PRESS\n");
    LOG_TAB++;

    if (on_subwidgets_mouse_press(btn))
    {
        LOG_TAB--;
        return true;
    }

    status = WIDGET_UPDATED;
    update_ancestral_status(WIDGET_UPDATED);

    LOG_TAB--;
    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool main_window_t::set_tool_manager_tool(widget_t *self, void *args_, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == nullptr, false);
    (void) btn;

    tool_button_args *args = (tool_button_args *) args_;
    if (args->tool == nullptr) return false;

    args->window->tool_manager.set_tool(args->tool);

    self->status = WIDGET_UPDATED;
    self->update_ancestral_status(WIDGET_UPDATED);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool main_window_t::set_tool_manager_color(widget_t *self, void *args_, const MOUSE_BUTTON_TYPE &btn)
{
    LOG_VERIFY(active == nullptr, false);
    (void) btn;

    color_button_args *args = (color_button_args *) args_;
    args->window->tool_manager.set_color(args->color);

    self->status = WIDGET_UPDATED;
    self->update_ancestral_status(WIDGET_UPDATED);

    return true;
}

//--------------------------------------------------------------------------------------------------

main_window_t::main_window_t(const rectangle_t &region_):
window_t             (region_, Red_theme),

tool_button_args_arr (nullptr),
color_button_args_arr(nullptr),

rectangle_tool       (new rectangle_tool_t),
ellipse_tool         (new ellipse_tool_t),
line_tool            (new line_tool_t),
tool_manager         (rectangle_tool, color_t::Black),

toolbar              (button_t::button_delete),
palette              (button_t::button_delete),
canvas               (&tool_manager)
{
    toolbar_create();
    palette_create();
    canvas_create ();
}

//--------------------------------------------------------------------------------------------------

main_window_t::~main_window_t()
{
    delete[]  tool_button_args_arr;
    delete[] color_button_args_arr;

    delete rectangle_tool;
    delete ellipse_tool;
    delete line_tool;
}

//--------------------------------------------------------------------------------------------------

void main_window_t::toolbar_create()
{
    rectangle_t toolbar_region
        (visible.region.ld_corner + vec2d(0, HEADER_MENU_HEIGHT),
         visible.region.ld_corner + vec2d(0, HEADER_MENU_HEIGHT) + TOOLBAR_SIZE);

    toolbar.set_region(toolbar_region);
    toolbar.color = window_t::Blue_theme;

    toolbar_create_tool_btns();

    register_subwidget(&toolbar);
}

//--------------------------------------------------------------------------------------------------

void main_window_t::toolbar_create_tool_btns()
{
    // порядок инструментов в массиве должен соответствовать порядку имен текстур
    // инструментов в button_t::BUTTON_TEXTURE_NAME_TYPE.
    tool_button_args_arr = new tool_button_args[TOOLBAR_BTN_NUMS];
    tool_button_args_arr[0] = {.window = this, .tool = nullptr};
    tool_button_args_arr[1] = {.window = this, .tool = rectangle_tool};
    tool_button_args_arr[2] = {.window = this, .tool = ellipse_tool};
    tool_button_args_arr[3] = {.window = this, .tool = nullptr};
    tool_button_args_arr[4] = {.window = this, .tool = nullptr};
    tool_button_args_arr[5] = {.window = this, .tool = line_tool};
    tool_button_args_arr[6] = {.window = this, .tool = nullptr};
    tool_button_args_arr[7] = {.window = this, .tool = nullptr};

    vec2d l_column_off(20, 10);
    vec2d r_column_off(TOOLBAR_SIZE.x - 20 - TOOLBAR_BTN_SIZE.x, 10);

    size_t tool_cnt = 0;
    size_t texture  = button_t::FILL_OFF_TOOL;

    for (; tool_cnt < TOOLBAR_BTN_NUMS / 2; ++tool_cnt)
    {
        toolbar_create_tool_btn((button_t::BUTTON_TEXTURE_NAME_TYPE) texture, tool_button_args_arr + tool_cnt, l_column_off);
        l_column_off.y += TOOLBAR_BTN_SIZE.y + 10;
        texture        += 2;
    }

    for (; tool_cnt < TOOLBAR_BTN_NUMS; ++tool_cnt)
    {
        toolbar_create_tool_btn((button_t::BUTTON_TEXTURE_NAME_TYPE) texture, tool_button_args_arr + tool_cnt, r_column_off);
        r_column_off.y += TOOLBAR_BTN_SIZE.y + 10;
        texture        += 2;
    }
}

//--------------------------------------------------------------------------------------------------

void main_window_t::toolbar_create_tool_btn(const button_t::BUTTON_TEXTURE_NAME_TYPE texture, tool_button_args *args, const vec2d &btn_off)
{
    rectangle_t button_region
        (toolbar.visible.region.ld_corner + btn_off,
         toolbar.visible.region.ld_corner + btn_off + TOOLBAR_BTN_SIZE);

    texture_button_t *button = new texture_button_t(texture, button_region);
    button->set_funcs(nullptr, nullptr,
                      set_tool_manager_tool, nullptr, nullptr);
    button->set_args (args);

    toolbar.register_button(button);
}

//--------------------------------------------------------------------------------------------------

void main_window_t::palette_create()
{
    rectangle_t palette_region
        (visible.region.lu_corner() - vec2d(0, PALETTE_SIZE.y),
         visible.region.lu_corner() - vec2d(0, PALETTE_SIZE.y) + PALETTE_SIZE);

    palette.set_region(palette_region);
    palette.color = window_t::Blue_theme;

    palette_create_color_btns();

    register_subwidget(&palette);
}

//--------------------------------------------------------------------------------------------------

void main_window_t::palette_create_color_btns()
{
    // порядок цветов в массиве должен соответствовать порядку имен текстур
    // цветов в button_t::BUTTON_TEXTURE_NAME_TYPE.
    color_button_args_arr = new color_button_args[PALETTE_BTN_NUMS];
    color_button_args_arr[0] = {.window = this, .color = color_t::White};
    color_button_args_arr[1] = {.window = this, .color = color_t::Blue};
    color_button_args_arr[2] = {.window = this, .color = color_t::Red};
    color_button_args_arr[3] = {.window = this, .color = color_t::Orange};
    color_button_args_arr[4] = {.window = this, .color = color_t::Green};
    color_button_args_arr[5] = {.window = this, .color = color_t::Black};

    vec2d l_column_off(20, 10);
    vec2d r_column_off(PALETTE_SIZE.x - 20 - PALETTE_BTN_SIZE.x, 10);

    size_t color_cnt = 0;
    size_t texture   = button_t::WHITE_OFF_COLOR;

    for (; color_cnt < PALETTE_BTN_NUMS / 2; ++color_cnt)
    {
        palette_create_color_btn((button_t::BUTTON_TEXTURE_NAME_TYPE) texture, color_button_args_arr + color_cnt, l_column_off);
        l_column_off.y += PALETTE_BTN_SIZE.y + 10;
        texture        += 2;
    }

    for (; color_cnt < PALETTE_BTN_NUMS; ++color_cnt)
    {
        palette_create_color_btn((button_t::BUTTON_TEXTURE_NAME_TYPE) texture, color_button_args_arr + color_cnt, r_column_off);
        r_column_off.y += PALETTE_BTN_SIZE.y + 10;
        texture        += 2;
    }
}

//--------------------------------------------------------------------------------------------------

void main_window_t::palette_create_color_btn(const button_t::BUTTON_TEXTURE_NAME_TYPE texture, color_button_args *args, const vec2d &btn_off)
{
    rectangle_t button_region
        (palette.visible.region.ld_corner + btn_off,
         palette.visible.region.ld_corner + btn_off + PALETTE_BTN_SIZE);

    texture_button_t *button = new texture_button_t(texture, button_region);
    button->set_funcs(nullptr, nullptr,
                      set_tool_manager_color, nullptr, nullptr);
    button->set_args(args);

    palette.register_button(button);
}

//--------------------------------------------------------------------------------------------------

void main_window_t::canvas_create()
{
    rectangle_t canvas_region
        (visible.region.ld_corner + vec2d(TOOLBAR_SIZE.x + 30, HEADER_MENU_HEIGHT + 30),
         visible.region.ru_corner - vec2d(30, 30));

    canvas.set_region(canvas_region);
    register_subwidget(&canvas);
}
