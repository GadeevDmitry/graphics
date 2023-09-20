#ifndef GAS_SCENE_H
#define GAS_SCENE_H

#include <list/list.h>

#include "draw.h"
#include "piston.h"
#include "molecule.h"
#include "rectangle.h"
#include "material_point.h"

//==================================================================================================

class gas_scene_t
{
private:

    piston_t    piston;
    rectangle_t vessel;
    list      moleculs;

    static void molecule_ptr_dtor(void *ptr) { delete *(molecule_t **)ptr; }

public:
    explicit gas_scene_t(const piston_t &piston_, const rectangle_t &vessel_):
    piston(piston_),
    vessel(vessel_)
    {
        list_ctor(&moleculs, sizeof(molecule_t *), gas_scene_t::molecule_ptr_dtor);

        int vessel_width  = (int) (vessel.ru_corner.x - vessel.ld_corner.x - molecule_t::MOLECULE_SIZE);
        int vessel_height = (int) (vessel.ru_corner.y - vessel.ld_corner.y - molecule_t::MOLECULE_SIZE);

        for (size_t index = 0; index < 100; ++index)
        {
            vec2d molecule_pos   = vec2d(vessel.ld_corner.x + molecule_t::MOLECULE_SIZE/2 + rand() % vessel_width,
                                         vessel.ld_corner.y + molecule_t::MOLECULE_SIZE/2 + rand() % vessel_height);
            vec2d molecule_speed = vec2d(rand() % 100, rand() % 100);

            light_molecule_t *molecule = new light_molecule_t(material_point_t(molecule_pos, molecule_speed));
            list_push_back(&moleculs, &molecule);
        }
    }

    ~gas_scene_t()
    {
        list_dtor(&moleculs);
    }

    void refresh(const double frame_time);
    void draw(sf::RenderWindow &wnd) const
    {
        draw_hollow_rectangle(vessel, wnd, sf::Color::White);
        piston.draw          (        wnd, sf::Color::White);

        if (moleculs.size == 0) return;

        molecule_t **cur_molecule_ptr = (molecule_t **) list_front(&moleculs);
        for (size_t index = 0; index < moleculs.size; ++index)
        {
            molecule_t &cur_molecule = **cur_molecule_ptr;
            cur_molecule.draw(wnd);

            cur_molecule_ptr = (molecule_t **) list_next(&moleculs, cur_molecule_ptr);
        }
    }
};

#endif // GAS_SCENE_H
