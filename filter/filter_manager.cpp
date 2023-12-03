#include <stdio.h>

#include "filter_manager.h"
#include "plugin/host/HostRenderTargetI.h"

#include "data_structs/include/log.h"

//==================================================================================================

void filter_manager_t::apply_last_filter(render_texture_t &perm) const
{
    LOG_VERIFY(last_filter != nullptr, (void) 0);

    host::HostRenderTargetI permI(perm);
    last_filter->apply(&permI);
}
