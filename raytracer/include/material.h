#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

//==================================================================================================

class material_t
{
public:
    double   diff_coeff;
    double   refl_coeff;
    unsigned spec_degree;
    color_t  own_col;

    explicit material_t(const double diff_coeff_ = 0, const double refl_coeff_ = 0,
                        const unsigned spec_degree_ = 0, const color_t &own_col_ = color_t()):
    diff_coeff (diff_coeff_),
    refl_coeff (refl_coeff_),
    spec_degree(spec_degree_),
    own_col(own_col_)
    {}

    explicit material_t(const material_t &base, const color_t &own_col_):
    diff_coeff (base.diff_coeff),
    refl_coeff (base.refl_coeff),
    spec_degree(base.spec_degree),
    own_col(own_col_)
    {}

    static const material_t Plastic;
    static const material_t Mirror;
};

#endif // MATERIAL_H
