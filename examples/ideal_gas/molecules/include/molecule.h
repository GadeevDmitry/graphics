#ifndef MOLECULE_H
#define MOLECULE_H

#include "draw.h"
#include "vec2d.h"
#include "circle.h"
#include "segment.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

enum MOLECULE_TYPE
{
    HEAVY_MOLECULE,
    LIGHT_MOLECULE,

    MOLECULE_TYPE_MAX,
};

//--------------------------------------------------------------------------------------------------

class molecule_t
{
public:
    const MOLECULE_TYPE type;
    unsigned          weight;

    circle_t shape;
    vec2d    speed;

    explicit molecule_t(const MOLECULE_TYPE type_,
                        const unsigned    weight_ = 1,

                        const circle_t &shape_ = circle_t(),
                        const vec2d    &speed_ = vec2d()):
    type  (type_),
    weight(weight_),

    shape(shape_),
    speed(speed_)
    {}

    virtual ~molecule_t() {}
    virtual void draw(sf::RenderTarget &wnd) const = 0;

    void refresh(const double frame_time) { shape.center += frame_time * speed; }

    bool try_hit_segment(const double frame_time, const segment_t &target);
    bool try_hit_circle (const double frame_time, const circle_t  &target, const vec2d &target_speed, double &hit_time) const;
};

//--------------------------------------------------------------------------------------------------

class heavy_molecule_t: public molecule_t
{
public:
    explicit heavy_molecule_t(const unsigned weight_ = 2,
                              const circle_t &shape_ = circle_t(),
                              const vec2d    &speed_ = vec2d()):
    molecule_t(HEAVY_MOLECULE, weight_, shape_, speed_)
    {}

    virtual void draw(sf::RenderTarget &wnd) const override
    {
        rectangle_t image = rectangle_t(shape.center - vec2d(shape.radius, shape.radius),
                                        shape.center + vec2d(shape.radius, shape.radius));

        draw_filled_rectangle(image, wnd, sf::Color::Red);
    }
};

//--------------------------------------------------------------------------------------------------

class light_molecule_t: public molecule_t
{
public:
    explicit light_molecule_t(const circle_t &shape_ = circle_t(),
                              const vec2d    &speed_ = vec2d()):
    molecule_t(LIGHT_MOLECULE, 1, shape_, speed_)
    {}

    virtual void draw(sf::RenderTarget &wnd) const override
    {
        draw_filled_circle(shape, wnd, sf::Color::Blue);
    }

};

#endif // MOLECULE_H
