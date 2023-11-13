#ifndef FILTER_MANAGER_H
#define FILTER_MANAGER_H

#include "filter.h"
#include "widget/canvas.h"

//==================================================================================================

class filter_manager_t
{
// member functions
public:
             inline filter_manager_t();
    explicit inline filter_manager_t(filter_t *last_filter);

    void inline        set_filter(filter_t *filter);
    void inline   set_last_filter();
    void inline apply_last_filter(render_texture_t &perm) const;

// member data
private:
    filter_t *last_filter;
};

//--------------------------------------------------------------------------------------------------

inline filter_manager_t::filter_manager_t():
last_filter(nullptr)
{}

//--------------------------------------------------------------------------------------------------

inline filter_manager_t::filter_manager_t(filter_t *last_filter_):
last_filter(last_filter_)
{}

//--------------------------------------------------------------------------------------------------

inline void filter_manager_t::set_filter(filter_t *filter)
{
    last_filter = filter;
    canvas_t::active_instrument = canvas_t::FILTER;
}

//--------------------------------------------------------------------------------------------------

inline void filter_manager_t::set_last_filter()
{
    canvas_t::active_instrument = canvas_t::FILTER;
}

//--------------------------------------------------------------------------------------------------

inline void filter_manager_t::apply_last_filter(render_texture_t &perm) const
{
    last_filter->apply(perm);
}

#endif // FILTER_MANAGER_H
