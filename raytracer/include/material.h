#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

//==================================================================================================

class material_t
{
private:
    double   diff_coeff;
    unsigned spec_degree;

public:
    color_t own_col;

    explicit material_t(const double diff_coeff_ = 0, const unsigned spec_degree_ = 0, const color_t &own_col_ = color_t()):
    diff_coeff(diff_coeff_),
    spec_degree(spec_degree_),
    own_col(own_col_)
    {}

    explicit material_t(const material_t &base, const color_t &own_col_):
    diff_coeff(base.diff_coeff),
    spec_degree(base.spec_degree),
    own_col(own_col_)
    {}

    double   get_diff_coeff () { return diff_coeff; }
    unsigned get_spec_degree() { return spec_degree; }

    static const material_t Plastic;
};

#endif // MATERIAL_H
