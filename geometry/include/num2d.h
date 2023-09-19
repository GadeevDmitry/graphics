#ifndef NUM2D_H
#define NUM2D_H

#include <math.h>
#include <algorithm/algorithm.h>

//==================================================================================================

class num2d
{
public:
    double x;
    double y;

    explicit num2d(double x_ = 0, double y_ = 0):
    x(x_),
    y(y_)
    {}

    ~num2d() {x = NAN; y = NAN; }

    num2d operator +(const num2d &add) const { return num2d(x + add.x, y + add.y); }
    num2d operator -(const num2d &sub) const { return num2d(x - sub.x, y - sub.y); }
    num2d operator *(const double mul) const { return num2d(x * mul  , y * mul  ); }
    num2d operator /(const double div) const { return (*this) * (1 / div); }
    num2d operator -()                 const { return (*this) * (-1); }

    num2d &operator +=(const num2d &add) { return *this = (*this) + add; }
    num2d &operator -=(const num2d &sub) { return *this = (*this) - sub; }
    num2d &operator *=(const double mul) { return *this = (*this) * mul; }
    num2d &operator /=(const double div) { return *this = (*this) / div; }

    friend num2d operator *(const double mul, const num2d &vec) { return vec * mul; }

    bool operator ==(const num2d &cmp) const { return dblcmp(x, cmp.x) == 0 && dblcmp(y, cmp.y) == 0; }
    bool operator !=(const num2d &cmp) const { return !((*this) == cmp); }
};

#endif // NUM2D_H
