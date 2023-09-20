#ifndef MOLECULE_H
#define MOLECULE_H

#include "color.h"
#include "piston.h"
#include "segment.h"
#include "material_point.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

enum MOLECULE_TYPE
{
    HEAVY_MOLECULE,
    LIGHT_MOLECULE,
};

//--------------------------------------------------------------------------------------------------

class molecule_t
{
protected:
    MOLECULE_TYPE type;

public:
    material_point_t center;
    unsigned         weight;

    explicit molecule_t(const MOLECULE_TYPE     type_   = LIGHT_MOLECULE,
                        const material_point_t &center_ = material_point_t(),
                        const unsigned          weight_ = 1):
    type(type_),
    center(center_),
    weight(weight_)
    {}

    static const double MOLECULE_SIZE;

    virtual ~molecule_t() {}
    virtual void draw(sf::RenderWindow &wnd) const = 0;

    MOLECULE_TYPE get_type() { return type; }

    bool try_hit_segment (const double frame_time, const segment_t  &target);
    bool try_hit_piston  (const double frame_time, const piston_t   &target);
    bool try_hit_molecule(const double frame_time, const molecule_t &target, vec2d &hit_point) const;

    void refresh(const double frame_time) { center.refresh(frame_time); }
};

//--------------------------------------------------------------------------------------------------

class heavy_molecule_t: public molecule_t
{
public:
    explicit heavy_molecule_t(const material_point_t &center_ = material_point_t(),
                              const unsigned          weight_ = 2):
    molecule_t(HEAVY_MOLECULE, center_, weight_)
    {}

    void draw(sf::RenderWindow &wnd) const override;
};

//--------------------------------------------------------------------------------------------------

class light_molecule_t: public molecule_t
{
public:
    explicit light_molecule_t(const material_point_t &center_ = material_point_t()):
    molecule_t(LIGHT_MOLECULE, center_, 1)
    {}

    void draw(sf::RenderWindow &wnd) const override;
};

#endif // MOLECULE_H
