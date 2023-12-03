#ifndef EDIT_BOX_H
#define EDIT_BOX_H

#include "color_button.h"
#include "data_structs/include/algorithm.h"

//==================================================================================================

class edit_box_controller_t: public widget_controller_t
{
// virtual
public:
    virtual bool on_key_press    (widget_t *handle, const eventable::key_context_t   &context, const KEY_TYPE          &key) override;
    virtual bool on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class edit_box_t: public color_button_t
{
// static
protected:
    static const unsigned MAX_STRING_SIZE;
    static edit_box_controller_t edit_box_controller;

// member functions
public:
    explicit edit_box_t(                              const size_t char_size);
    explicit edit_box_t(const rectangle_t &enclosing, const size_t char_size);
    inline  ~edit_box_t();

    void        create_texture();
    void        set_string    (const char *);
    const char *get_string    () const;
protected:
    void insert    (const char inserted);
    void erase     ();
    void cursor_inc();
    void cursor_dec();
private:
    void ctor();
    void update_texture();

// virtual
public:
    virtual void render(render_texture_t &wnd) override;
protected:
    virtual void inline dump_class_name() const override;

// member data
protected:
    text_t    text;
private:
    buffer    string;
    unsigned  cursor_off;
    texture_t texture;

// friends
    friend edit_box_controller_t;
};

//--------------------------------------------------------------------------------------------------

inline edit_box_t::~edit_box_t()
{
    buffer_dtor(&string);
}

//--------------------------------------------------------------------------------------------------

inline void edit_box_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("edit_box_t", "");
}

#endif // EDIT_BOX_H
