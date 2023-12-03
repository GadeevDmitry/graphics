#ifndef FILTER_MANAGER_H
#define FILTER_MANAGER_H

#include "plugin/standart/Filter.h"
#include "widget/canvas.h"

//==================================================================================================

using plugin::FilterI;

namespace host
{
    class HostFilterManagerI;
};

class filter_manager_t
{
// member functions
public:
             inline  filter_manager_t();
    explicit inline  filter_manager_t(FilterI *last_filter);
             inline ~filter_manager_t() {}

    void inline        set_filter(FilterI *filter);
    void inline   set_last_filter();
    void        apply_last_filter(render_texture_t &perm) const;

// member data
private:
    FilterI *last_filter;

// friends
    friend host::HostFilterManagerI;
};

//--------------------------------------------------------------------------------------------------

inline filter_manager_t::filter_manager_t():
last_filter(nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline filter_manager_t::filter_manager_t(FilterI *last_filter_):
last_filter(last_filter_)
{}

//--------------------------------------------------------------------------------------------------

inline void filter_manager_t::set_filter(FilterI *filter)
{
    last_filter = filter;
    canvas_t::active_instrument = canvas_t::FILTER;
}

//--------------------------------------------------------------------------------------------------

inline void filter_manager_t::set_last_filter()
{
    canvas_t::active_instrument = canvas_t::FILTER;
}

#endif // FILTER_MANAGER_H
