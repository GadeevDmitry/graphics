#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "equation_solver.h"
#include "algorithm.h"

//==================================================================================================

int linear_solver(const double a, const double b, double &x)
{
    if (dblcmp(a, 0) == 0)
    {
        if (dblcmp(b, 0) == 0) return -1; // 0x + 0 = 0
        else                   return  0; // 0x + b = 0
    }

    x = -b/a;
    return 1;
}

//--------------------------------------------------------------------------------------------------

int square_solver(const double a, const double b, const double c,
                  double &x1, double &x2)
{
    if (dblcmp(a, 0) == 0) return linear_solver(b, c, x1);

    double D = b*b - 4*a*c;
    int sign = dblcmp(D, 0);

    if (sign <  0) return 0;
    if (sign == 0)
    {
        x1 = -b / (2*a);
        return 1;
    }

    x1 = (-b - sqrt(D)) / (2*a);
    x2 = (-b + sqrt(D)) / (2*a);
    return 2;
}
