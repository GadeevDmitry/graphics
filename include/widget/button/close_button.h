#ifndef CLOSE_BUTTON_H
#define CLOSE_BUTTON_H

#include "widget/button/texture_button.h"

//==================================================================================================

class close_button_controller_t: public widget_controller_t
{
// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
};

//--------------------------------------------------------------------------------------------------

inline bool close_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class close_button_t: public texture_button_t
{
// types
public:
    enum BUTTON_TEXTURE_NAME_TYPE
    {
        BUTTON_TEXTURE_NAME_TYPE_UNKNOWN = -1,

        RED,
        BLUE,
        GREEN,

        BUTTON_TEXTURE_NAME_COUNT
    };

// static
public:
    static close_button_controller_t close_button_controller;
    static void load_textures();
private:
    static texture_t   BUTTON_TEXTURES[];
    static const char *BUTTON_TEXTURES_FILES[];

// member functions
public:
    explicit inline close_button_t(widget_t &to_close,                               const BUTTON_TEXTURE_NAME_TYPE &texture = RED);
    explicit inline close_button_t(widget_t &to_close, const rectangle_t &enclosing, const BUTTON_TEXTURE_NAME_TYPE &texture = RED);

// virtual
protected:
    virtual void inline dump_class_name() const override;

// member data
public:
    widget_t &to_close;
};

//--------------------------------------------------------------------------------------------------

inline close_button_t::close_button_t(widget_t &to_close_, const BUTTON_TEXTURE_NAME_TYPE &texture_):
texture_button_t(close_button_controller),
to_close        (to_close_)
{
    LOG_VERIFY(texture_ > BUTTON_TEXTURE_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(texture_ < BUTTON_TEXTURE_NAME_COUNT       , ;);
    texture = BUTTON_TEXTURES + texture_;
}

//--------------------------------------------------------------------------------------------------

inline close_button_t::close_button_t(widget_t &to_close_, const rectangle_t &enclosing_, const BUTTON_TEXTURE_NAME_TYPE &texture_):
texture_button_t(close_button_controller, enclosing_),
to_close        (to_close_)
{
    LOG_VERIFY(texture_ > BUTTON_TEXTURE_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(texture_ < BUTTON_TEXTURE_NAME_COUNT       , ;);
    texture = BUTTON_TEXTURES + texture_;
}

//--------------------------------------------------------------------------------------------------

inline void close_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("close_button_t", "");
}

#endif // CLOSE_BUTTON_H
