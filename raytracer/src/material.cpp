#include <stdio.h>

#include "color.h"
#include "material.h"

//==================================================================================================

const material_t material_t::Plastic = material_t(0.6, 0   , 15);
const material_t material_t::Mirror  = material_t(0  , 0.99, 100, color_t::White);
