#ifndef PALETTE_BUTTON_H
#define PALETTE_BUTTON_H

#include "widget/button/texture_button.h"
#include "tool/tool_manager.h"

//==================================================================================================

class palette_button_controller_t: public widget_controller_t
{
// member functions
public:
    explicit inline palette_button_controller_t(tool_manager_t &tool_manager);

// virtual
public:
    virtual bool        on_mouse_press  (widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;
    virtual bool inline on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn) override;

// member data
private:
    tool_manager_t &tool_manager;
};

//--------------------------------------------------------------------------------------------------

inline palette_button_controller_t::palette_button_controller_t(tool_manager_t &tool_manager_):
tool_manager(tool_manager_)
{}

//--------------------------------------------------------------------------------------------------

inline bool palette_button_controller_t::on_mouse_release(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    (void) handle;
    (void) context;
    (void) btn;
    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class palette_button_t: public texture_button_t
{
// types
public:
    enum BUTTON_TEXTURE_NAME_TYPE
    {
        BUTTON_TEXTURE_NAME_TYPE_UNKNOWN = -1,

        WHITE_ON,
        BLUE_ON,
        RED_ON,
        ORANGE_ON,
        GREEN_ON,
        BLACK_ON,

        WHITE_OFF,
        BLUE_OFF,
        RED_OFF,
        ORANGE_OFF,
        GREEN_OFF,
        BLACK_OFF,

        BUTTON_TEXTURE_NAME_COUNT,
    };

// static
public:
    static void load_textures();
private:
    static texture_t   BUTTON_TEXTURES[];
    static const char *BUTTON_TEXTURES_FILES[];

// member functions
public:
    explicit inline palette_button_t(widget_controller_t &controller,                               const BUTTON_TEXTURE_NAME_TYPE &texture, const color_t &color);
    explicit inline palette_button_t(widget_controller_t &controller, const rectangle_t &enclosing, const BUTTON_TEXTURE_NAME_TYPE &texture, const color_t &color);

// virtual
protected:
    void inline dump_class_name() const override;

// member data
public:
    color_t color;
};

//--------------------------------------------------------------------------------------------------

inline palette_button_t::palette_button_t(widget_controller_t &controller_, const BUTTON_TEXTURE_NAME_TYPE &texture_, const color_t &color_):
texture_button_t(controller_),
color           (color_)
{
    LOG_VERIFY(texture_ > BUTTON_TEXTURE_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(texture_ < BUTTON_TEXTURE_NAME_COUNT       , ;);
    texture = BUTTON_TEXTURES + texture_;
}

//--------------------------------------------------------------------------------------------------

inline palette_button_t::palette_button_t(widget_controller_t &controller_, const rectangle_t &enclosing_, const BUTTON_TEXTURE_NAME_TYPE &texture_, const color_t &color_):
texture_button_t(controller_, enclosing_),
color           (color_)
{
    LOG_VERIFY(texture_ > BUTTON_TEXTURE_NAME_TYPE_UNKNOWN, ;);
    LOG_VERIFY(texture_ < BUTTON_TEXTURE_NAME_COUNT       , ;);
    texture = BUTTON_TEXTURES + texture_;
}

//--------------------------------------------------------------------------------------------------

inline void palette_button_t::dump_class_name() const
{
    LOG_TAB_SERVICE_MESSAGE("palette_button_t", "");
}

#endif // PALETTE_BUTTON_H
