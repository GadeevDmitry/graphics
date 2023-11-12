#include <stdio.h>
#include "renderable.h"

//==================================================================================================

void renderable::dump() const
{
    LOG_TAB_SERVICE_MESSAGE("renderable\n{", "\n");
    LOG_TAB++;

    LOG_TAB_MESSAGE("enclosing\n");
    enclosing.dump();

    LOG_TAB_MESSAGE("\nown_visible\n");
    own_visible.dump();

    LOG_TAB_MESSAGE("\nsub_enclosing\n");
    sub_enclosing.dump();

    LOG_TAB--;
    LOG_TAB_SERVICE_MESSAGE("}", "\n\n");
}
