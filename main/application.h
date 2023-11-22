#ifndef APPLICATION_H
#define APPLICATION_H

#include "event/event_manager.h"

#include "tool/tool_manager.h"
#include "tool/shape_tool/line_tool.h"
#include "tool/shape_tool/ellipse_tool.h"
#include "tool/shape_tool/rectangle_tool.h"

#include "filter/filter_manager.h"
#include "filter/brightness_filter.h"

#include "widget/desktop.h"
#include "widget/window/main_window.h"
#include "widget/window/canvas_window.h"
#include "widget/window/palette_window.h"
#include "widget/window/toolbar_window.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class application_t
{
// static
public:
    static void load_textures();
    static void load_fonts   ();
    static void show         (sf::RenderWindow &sfml_wnd, render_texture_t &render_tex);

// member functions
public:
    explicit application_t(const vec2d &wnd_size);

    void dump        () const;
    void graphic_dump(                            render_texture_t &render_tex) const;
    void process     (sf::RenderWindow &sfml_wnd, render_texture_t &render_tex);
private:
    void render (sf::RenderWindow &sfml_wnd, render_texture_t &render_tex);
    void create ();

// member data
private:
    event_manager_t     event_manager;

    line_tool_t         line_tool;
    ellipse_tool_t      ellipse_tool;
    rectangle_tool_t    rectangle_tool;
    tool_manager_t      tool_manager;

    brightness_filter_t brightness_filter;
    filter_manager_t    filter_manager;

    window_controller_t window_controller;
    canvas_window_t     *canvas_window;
    palette_window_t    *palette_window;
    toolbar_window_t    *toolbar_window;
    main_window_t       *main_window;

    desktop_t           desktop;
};

#endif // APPLICATION_H