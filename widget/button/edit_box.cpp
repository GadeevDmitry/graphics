#include <stdio.h>
#include <string.h>

#include "window.h"
#include "button/edit_box.h"

//==================================================================================================

const unsigned        edit_box_t::MAX_STRING_SIZE = 100;
edit_box_controller_t edit_box_t::edit_box_controller;

//==================================================================================================

bool edit_box_controller_t::on_key_press(widget_t *handle, const eventable::key_context_t &context, const KEY_TYPE &key)
{
    edit_box_t *edit_box = (edit_box_t *) handle;
    if (widget_t::active != edit_box) return false;

    if (key ==  Backspace) edit_box->erase();
    else if (key ==  Left) edit_box->cursor_dec();
    else if (key == Right) edit_box->cursor_inc();
    else
    {
        if      (key >= A    && key <= Z   ) edit_box->insert('a' + key - A);
        else if (key >= Num0 && key <= Num9) edit_box->insert('0' + key - Num0);
        else if (key == Period)              edit_box->insert('.');
    }

    edit_box->status = widget_t::WIDGET_ACTIVATED;
    edit_box->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//--------------------------------------------------------------------------------------------------

bool edit_box_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    edit_box_t *edit_box = (edit_box_t *) handle;

    if (widget_t::active != edit_box)
    {
        widget_t::active = edit_box;
        edit_box->status = widget_t::WIDGET_ACTIVATED;
        edit_box->update_ancestral_status(widget_t::WIDGET_ACTIVATED);

        return true;
    }
    else if (!edit_box->enclosing.is_point_inside(context.pos))
    {
        widget_t::active = nullptr;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------

bool edit_box_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

edit_box_t::edit_box_t(const size_t char_size):
color_button_t(edit_box_controller, color_t::Black, window_t::Light_theme),
text          (&font_t::get_font_by_name(font_t::EDU_QLD), nullptr, color_t::Black, char_size),
cursor_off    (3),
texture       ()
{
    ctor();
}

//--------------------------------------------------------------------------------------------------

edit_box_t::edit_box_t(const rectangle_t &enclosing_, const size_t char_size):
color_button_t(edit_box_controller, color_t::Black, window_t::Light_theme),
text          (&font_t::get_font_by_name(font_t::EDU_QLD), nullptr, color_t::Black, char_size),
cursor_off    (3),
texture       ()
{
    ctor();
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::ctor()
{
    buffer_ctor(&string, MAX_STRING_SIZE);
    text.string = string.beg;
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::create_texture()
{
    color_button_t::create_texture();

    render_texture_t temp((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);
    temp.clear(color_t::Transparent);

    temp.display();
    texture = temp.get_texture();
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::update_texture()
{
    render_texture_t temp((unsigned) enclosing.get_size().x, (unsigned) enclosing.get_size().y);
    temp.draw_text(text, vec2d(5, 5));

    temp.display();
    texture = temp.get_texture();
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::set_string(const char *value)
{
    string.pos = string.beg;
    buffer_write(&string, value, strlen(value) + 1);
    *buffer_back(&string) = '\0';

    string.pos = string.beg;
    cursor_off = 3;

    update_texture();
}

//--------------------------------------------------------------------------------------------------

const char *edit_box_t::get_string() const
{
    return string.beg;
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::insert(const char inserted)
{
    if (string.pos >= buffer_back(&string)) return;
    if (buffer_back(&string)[-1] != '\0')   return;

    for (char *cnt = buffer_back(&string); cnt > string.pos; --cnt)
        cnt[0] = cnt[-1];

    string.pos[0] = inserted;
    string.pos++;
    cursor_off += text.font->get_char_size(inserted, text.character_size);

    update_texture();
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::erase()
{
    if (string.pos == string.beg) return;
    char erased = string.pos[-1];

    for (char *cnt = string.pos; cnt < buffer_end(&string); ++cnt)
        cnt[-1] = cnt[0];

    string.pos--;
    cursor_off -= text.font->get_char_size(erased, text.character_size);

    update_texture();
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::cursor_inc()
{
    if (*string.pos != '\0')
    {
        cursor_off += text.font->get_char_size(*string.pos, text.character_size);
        string.pos++;
    }
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::cursor_dec()
{
    if (string.pos != string.beg)
    {
        string.pos--;
        cursor_off -= text.font->get_char_size(*string.pos, text.character_size);
    }
}

//--------------------------------------------------------------------------------------------------

void edit_box_t::render(render_texture_t &wnd)
{
    color_button_t::render(wnd);
    wnd.draw_texture(texture, enclosing, own_visible);
    wnd.draw_rectangle(
        rectangle_t(vec2d(enclosing.ld_corner.x + cursor_off    , enclosing.ld_corner.y + 5),
                    vec2d(enclosing.ld_corner.x + cursor_off + 1, enclosing.ru_corner.y - 5)),
        text.color, own_visible);
}
