#ifndef PLUGIN_HOST_WIDGET_I_H
#define PLUGIN_HOST_WIDGET_I_H

#include "plugin/standart/Widget.h"
#include "widget/widget_container.h"

//==================================================================================================

using plugin::MouseContext;
using plugin::KeyboardContext;
using plugin::RenderTargetI;

namespace host
{
    class HostWidgetI: public plugin::WidgetI
    {
    // member functions
    public:
        explicit inline HostWidgetI(widget_container_t &root);

    // virtual
    public:
        virtual bool    inline on_mouse_move   (MouseContext    context) override;
        virtual bool    inline on_mouse_release(MouseContext    context) override;
        virtual bool    inline on_mouse_press  (MouseContext    context) override;
        virtual bool    inline on_key_press    (KeyboardContext context) override;
        virtual bool    inline on_key_release  (KeyboardContext context) override;
        virtual bool    inline on_clock        (uint64_t delta)          override;

	    virtual uint8_t inline get_priority    ()                        override;

        virtual void       register_subwidget(WidgetI* object) override;
        virtual void     unregister_subwidget(WidgetI* object) override;

        virtual vec2d   inline get_size      ()                override;
        virtual void    inline set_size      (vec2d size)      override;

        virtual vec2d   inline get_pos       ()                override;
        virtual void    inline set_pos       (vec2d pos)       override;

        virtual bool    inline isExtern      ()                override;

        virtual void    inline  set_parent   (WidgetI *root)   override;
        virtual WidgetI inline *get_parent   ()                override;

        virtual void    inline  move         (vec2d shift)     override;

        virtual bool    inline get_available ()                override;
        virtual void    inline set_available (bool)            override;

        virtual void    inline render        (RenderTargetI *) override;
        virtual void    inline recalcRegion  ()                override;

        virtual         inline ~HostWidgetI  ()                override {}

    // member data
    private:
        widget_container_t &root;
    };

    //--------------------------------------------------------------------------------------------------

    inline HostWidgetI::HostWidgetI(widget_container_t &root_):
    root(root_)
    {}

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::on_mouse_move(MouseContext context)
    {
        (void) context;
        LOG_ERROR("HostWidgetI::on_mouse_move is not available for plugin\n");
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::on_mouse_release(MouseContext context)
    {
        (void) context;
        LOG_ERROR("HostWidgetI::on_mouse_release is not available for plugin\n");
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::on_mouse_press(MouseContext context)
    {
        (void) context;
        LOG_ERROR("HostWidgetI::on_mouse_press is not available for plugin\n");
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::on_key_press(KeyboardContext context)
    {
        (void) context;
        LOG_ERROR("HostWidgetI::on_key_press is not available for plugin\n");
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::on_key_release(KeyboardContext context)
    {
        (void) context;
        LOG_ERROR("HostWidgetI::on_key_release is not available for plugin\n");
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::on_clock(uint64_t delta)
    {
        (void) delta;
        LOG_ERROR("HostWidgetI::on_clock is not available for plugin\n");
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline uint8_t HostWidgetI::get_priority()
    {
        return (uint8_t) root.event_priority;
    }

    //--------------------------------------------------------------------------------------------------

    inline vec2d HostWidgetI::get_size()
    {
        return root.enclosing.get_size();
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::set_size(vec2d size)
    {
        (void) size;
        LOG_ERROR("HostWidgetI::set_size is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    inline vec2d HostWidgetI::get_pos()
    {
        return root.enclosing.ld_corner;
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::set_pos(vec2d pos)
    {
        (void) pos;
        LOG_ERROR("HostWidgetI::set_pos is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::isExtern()
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::set_parent(WidgetI *parent)
    {
        (void) parent;
        LOG_ERROR("HostWidgetI::set_parent is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    inline WidgetI *HostWidgetI::get_parent()
    {
        return nullptr;
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::move(vec2d shift)
    {
        (void) shift;
        LOG_ERROR("HostWidgetI::move is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    inline bool HostWidgetI::get_available()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::set_available(bool value)
    {
        (void) value;
        LOG_ERROR("HostWidgetI::set_available is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::render(RenderTargetI *wnd)
    {
        (void) wnd;
        LOG_ERROR("HostWidgetI::render is not available for plugin\n");
    }

    //--------------------------------------------------------------------------------------------------

    inline void HostWidgetI::recalcRegion()
    {
        LOG_ERROR("HostWidgetI::recalcRegion is not available for plugin\n");
    }
};

#endif // PLUGIN_HOST_WIDGET_I_H
