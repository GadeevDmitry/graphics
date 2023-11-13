#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <SFML/Graphics.hpp>

//==================================================================================================

class color_t
{
// static
public:
    static const color_t White;
    static const color_t Black;
    static const color_t Red;
    static const color_t Green;
    static const color_t Blue;
    static const color_t Orange;
    static const color_t Transparent;

    static color_t get_rand_color();

// member functions
public:
             inline  color_t();
    explicit inline  color_t(double r, double g, double b, double a = 1.0);
    explicit inline  color_t(const sf::Color &sf_color);
             inline ~color_t();

    sf::Color get_sfml_color     () const;
    void      maximize_brightness();

// member data
public:
    double r;
    double g;
    double b;
    double a;
};

//--------------------------------------------------------------------------------------------------

inline color_t::color_t():
r(0),
g(0),
b(0),
a(1.0)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::color_t(double r_, double g_, double b_, double a_):
r(r_),
g(g_),
b(b_),
a(a_)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::color_t(const sf::Color &sf_color):
r((double) sf_color.r / 255.0),
g((double) sf_color.g / 255.0),
b((double) sf_color.b / 255.0),
a((double) sf_color.a / 255.0)
{}

//--------------------------------------------------------------------------------------------------

inline color_t::~color_t()
{
    r = NAN;
    g = NAN;
    b = NAN;
    a = NAN;
}

#endif // COLOR_H
