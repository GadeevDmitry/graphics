#ifndef CANVAS_H
#define CANVAS_H

#include "widget.h"

//==================================================================================================

class tool_manager_t;

class canvas_t: public widget_t
{
///////////////////////////////////////////////
// FRIENDS
///////////////////////////////////////////////
friend tool_manager_t;

///////////////////////////////////////////////
// MEMBERS
///////////////////////////////////////////////
protected:
    render_texture_t perm;
    render_texture_t temp;
    tool_manager_t  *tool_manager;

    bool virtual inline on_key_press    (const KEY_TYPE          &key) override;
    bool virtual inline on_key_release  (const KEY_TYPE          &key) override;
    bool virtual        on_mouse_press  (const MOUSE_BUTTON_TYPE &btn) override; 
    bool virtual        on_mouse_release(const MOUSE_BUTTON_TYPE &btn) override;
    bool virtual        on_mouse_move   (const vec2d             &off) override;

public:
    explicit inline canvas_t(tool_manager_t *tool_manager_);
    explicit inline canvas_t(tool_manager_t *tool_manager_, const rectangle_t &region_);

    void inline set_region(const rectangle_t &region);
    void virtual render(render_texture_t &wnd) override;
};

//--------------------------------------------------------------------------------------------------

inline canvas_t::canvas_t(tool_manager_t *tool_manager_):
widget_t    (),
perm        (),
temp        (),
tool_manager(tool_manager_)
{}

//--------------------------------------------------------------------------------------------------

inline canvas_t::canvas_t(tool_manager_t *tool_manager_, const rectangle_t &region_):
widget_t    (region_),
perm        ((unsigned) region_.get_size().x, (unsigned) region_.get_size().y),
temp        ((unsigned) region_.get_size().x, (unsigned) region_.get_size().y),
tool_manager(tool_manager_)
{
    perm.clear(color_t::White);
    temp.clear(color_t::White);
}

//--------------------------------------------------------------------------------------------------

inline void canvas_t::set_region(const rectangle_t &region)
{
    visible.region = region;

    perm.create((unsigned) region.get_size().x, (unsigned) region.get_size().y);
    temp.create((unsigned) region.get_size().x, (unsigned) region.get_size().y);

    perm.clear(color_t::White);
    temp.clear(color_t::White);
}

//--------------------------------------------------------------------------------------------------

inline bool canvas_t::on_key_press(const KEY_TYPE &key)
{
    (void) key;
    return false;
}

//--------------------------------------------------------------------------------------------------

inline bool canvas_t::on_key_release(const KEY_TYPE &key)
{
    (void) key;
    return false;
}

#endif // CANVAS_H
