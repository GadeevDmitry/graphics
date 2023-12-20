#include <stdio.h>
#include <dlfcn.h>

#include "application.h"

//==================================================================================================

static sf::Vector2i recalc_mouse_pos(const sf::RenderWindow &sfml_wnd, const sf::Vector2i &mouse_pos);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char *application_t::SO_FILES[] =
{
    "plugin_examples/so/filter_fill.so",
    "plugin_examples/so/filter_monochrome.so",
//  "plugin_examples/so/filter_russian.so",

    "plugin_examples/so/tool_brush.so",
    "plugin_examples/so/tool_fill.so",
    "plugin_examples/so/tool_spray.so",
};

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
russia_filter    (),
filter_manager   (),

canvas_window    (new  canvas_window_t(               tool_manager, filter_manager, window_t::Dark_theme , "Canvas" )),
palette_window   (new palette_window_t(               tool_manager                , window_t::Light_theme, "Palette")),
toolbar_window   (new toolbar_window_t(               tool_manager                , window_t::Blue_theme , "Toolbar")),
main_window      (new    main_window_t(event_manager, tool_manager, filter_manager, window_t::Red_theme  , "Main"   )),

desktop          (rectangle_t(vec2d(0, 0), wnd_size)),

plugin_app       ()
{
    init_host();
    create();

    init_plugins();
}

//--------------------------------------------------------------------------------------------------

void application_t::init_host()
{
    event_manager.register_child(eventable_proxy(&desktop));

    main_window->set_filters(
        &brightness_filter, &russia_filter);

    main_window->set_tools(
        nullptr, &rectangle_tool, &ellipse_tool, nullptr,
        nullptr, &line_tool     , nullptr      , nullptr);

    toolbar_window->set_tools(
        nullptr, &rectangle_tool, &ellipse_tool, nullptr,
        nullptr, &line_tool     , nullptr      , nullptr);

    main_window->register_subwindow(canvas_window);
    main_window->register_subwindow(palette_window);
    main_window->register_subwindow(toolbar_window);

    desktop.register_window(main_window);
}

//--------------------------------------------------------------------------------------------------

void application_t::init_plugins()
{
    plugin_app.create(*main_window, event_manager, tool_manager, filter_manager);

    for (size_t cnt = 0; cnt * sizeof(char *) < sizeof(SO_FILES); ++cnt)
        load_plugin(SO_FILES[cnt]);
}

//--------------------------------------------------------------------------------------------------

void application_t::load_plugin(const char *so_file)
{
    void *handle = dlopen(so_file, RTLD_NOW | RTLD_LOCAL);
    if (!handle)
    {
        LOG_ERROR("CAN'T OPEN PLUGIN \"%s\": %s\n", so_file, dlerror());
        return;
    }

    plugin::Plugin *(*init_func) (plugin::App *app) = (plugin::Plugin *(*) (plugin::App *app)) dlsym(handle, "getInstance");
    if (!init_func)
    {
        LOG_ERROR("CAN'T FIND \"getInstance\": %s\n", dlerror());
        return;
    }

    plugin::Plugin *plug = init_func(&plugin_app);

    if (plug->type == plugin::InterfaceType::Filter)
    {
        FilterI *plugin_filter = (FilterI *) plug->get_interface();
        main_window->register_filter(plugin_filter, plug->name);
    }
    else
    {
        ToolI *plugin_tool = (ToolI *) plug->get_interface();
        main_window->register_tool(plugin_tool, plug->name);
    }
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

    main_window->register_canvas(canvas_window, "Canvas");

    desktop.recalc_regions();
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
    render_initial(sfml_wnd, rend_tex);
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

            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    event_manager.process_key_press_event
                        (eventable::key_context_t::convert_sfml_key(event.key.code));
                } break;

                case sf::Event::KeyReleased:
                {
                    event_manager.process_key_release_event
                        (eventable::key_context_t::convert_sfml_key(event.key.code));
                } break;

                case sf::Event::MouseButtonPressed:
                {
                    event_manager.process_mouse_press_event
                        (eventable::mouse_context_t::convert_sfml_btn(event.mouseButton.button));
                } break;

                case sf::Event::MouseButtonReleased:
                {
                    event_manager.process_mouse_release_event
                        (eventable::mouse_context_t::convert_sfml_btn(event.mouseButton.button));
                } break;

                case sf::Event::MouseMoved:
                {
                    event_manager.process_mouse_move_event
                        (eventable::mouse_context_t::convert_sfml_pos(recalc_mouse_pos(sfml_wnd, sf::Mouse::getPosition())));
                } break;

                default: break;
            }

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

void application_t::render_initial(sf::RenderWindow &sfml_wnd, render_texture_t &render_tex)
{
    desktop.render_initial(render_tex);
    render_tex.display();

    sf::Sprite spr(render_tex.get_sfml_texture());
    sfml_wnd.draw(spr);
    sfml_wnd.display();
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
