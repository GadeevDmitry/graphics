#include <stdio.h>
#include "application.h"

#include "widget/button/tool_button.h"
#include "widget/button/close_button.h"
#include "widget/button/palette_button.h"

//==================================================================================================

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos);

//==================================================================================================

void application_t::load_textures()
{
    tool_button_t   ::load_textures();
    close_button_t  ::load_textures();
    palette_button_t::load_textures();
}

//--------------------------------------------------------------------------------------------------

void application_t::load_fonts()
{
    font_t::load_fonts();
}

//--------------------------------------------------------------------------------------------------

application_t::application_t(const vec2d &wnd_size):
event_manager    (),

line_tool        (),
ellipse_tool     (),
rectangle_tool   (),
tool_manager     (&line_tool, color_t::Black),

brightness_filter(),
filter_manager   (),

window_controller(),
canvas_window    (new  canvas_window_t(window_controller, tool_manager  , filter_manager, window_t::Dark_theme , "Canvas" )),
palette_window   (new palette_window_t(window_controller, tool_manager                  , window_t::Light_theme, "Palette")),
toolbar_window   (new toolbar_window_t(window_controller, tool_manager                  , window_t::Blue_theme , "Toolbar")),
main_window      (new    main_window_t(window_controller,                 filter_manager, window_t::Red_theme  , "Main"   )),

desktop          (rectangle_t(vec2d(0, 0), wnd_size))
{
    event_manager.register_child(&desktop);

    main_window->set_filters(
        &brightness_filter);

    toolbar_window->set_tools(
        nullptr, &rectangle_tool, &ellipse_tool, nullptr,
        nullptr, &line_tool     , nullptr      , nullptr);

    main_window->register_subwindow(canvas_window);
    main_window->register_subwindow(palette_window);
    main_window->register_subwindow(toolbar_window);

    desktop.register_window(main_window);

    create();
}

//--------------------------------------------------------------------------------------------------

void application_t::create()
{
    main_window->create(desktop.enclosing);

    toolbar_window->create(rectangle_t(
        main_window->enclosing.ld_corner + vec2d(0, window_t::header_menu_height + main_window_t::main_menu_height + 10),
        toolbar_window_t::toolbar_size.x, window_t::header_menu_height + toolbar_window_t::toolbar_size.y));

    palette_window->create(rectangle_t(
        toolbar_window->enclosing.lu_corner() + vec2d(0, 10),
        palette_window_t::palette_size.x, window_t::header_menu_height + palette_window_t::palette_size.y));

    canvas_window->create(rectangle_t(
        toolbar_window->enclosing.rd_corner() + vec2d(30, 30),
        main_window   ->enclosing.ru_corner   - vec2d(30, 30)
    ));

    desktop.init_regions();
}

//--------------------------------------------------------------------------------------------------

void application_t::show(sf::RenderWindow &sfml_wnd, render_texture_t &rend_tex)
{
    sf::Sprite spr(rend_tex.get_sfml_texture());
    sfml_wnd.draw(spr);
    sfml_wnd.display();

    while (sfml_wnd.isOpen())
    {
        sf::Event event;
        while (sfml_wnd.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                sfml_wnd.close();
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wswitch-enum"

void application_t::process(sf::RenderWindow &sfml_wnd, render_texture_t &rend_tex)
{
    render(sfml_wnd, rend_tex);
    while (sfml_wnd.isOpen())
    {
        sf::Event event;
        while (sfml_wnd.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                sfml_wnd.close();
            }

            bool rerender = false;
            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                {
                    rerender = event_manager.process_mouse_press_event
                                (eventable::mouse_context_t::convert_sfml_btn(event.mouseButton.button));
                } break;

                case sf::Event::MouseButtonReleased:
                {
                    rerender = event_manager.process_mouse_release_event
                                (eventable::mouse_context_t::convert_sfml_btn(event.mouseButton.button));
                } break;

                case sf::Event::MouseMoved:
                {
                    rerender = event_manager.process_mouse_move_event
                                (eventable::mouse_context_t::convert_sfml_pos(recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition())));
                } break;

                default: break;
            }

            if (!rerender) continue;
            render(sfml_wnd, rend_tex);
        }
    }
}

#pragma GCC diagnostic pop

//--------------------------------------------------------------------------------------------------

void application_t::dump() const
{
    desktop.dump();
}

//--------------------------------------------------------------------------------------------------

void application_t::graphic_dump(render_texture_t &render_tex) const
{
    desktop.graphic_dump(render_tex);
    render_tex.display();
}

//--------------------------------------------------------------------------------------------------

void application_t::render(sf::RenderWindow &sfml_wnd, render_texture_t &render_tex)
{
    desktop.render(render_tex);
    render_tex.display();

    sf::Sprite spr(render_tex.get_sfml_texture());
    sfml_wnd.draw(spr);
    sfml_wnd.display();
}

//--------------------------------------------------------------------------------------------------

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos)
{
    return mouse_pos;
    return sf::Vector2i(mouse_pos.x, (int) sfml_wnd.getSize().y - mouse_pos.y);
}
