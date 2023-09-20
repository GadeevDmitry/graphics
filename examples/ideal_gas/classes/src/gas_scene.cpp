#include <stdio.h>
#include <stdlib.h>

#include "vec2d.h"
#include "segment.h"
#include "gas_scene.h"

#include "list/list.h"
#include "array/array.h"

//==================================================================================================

void gas_scene_t::refresh(const double frame_time)
{
    if (moleculs.size == 0) return;

    molecule_t **cur_molecule_ptr = (molecule_t **) list_front(&moleculs);

    vec2d vessel_ld(vessel.ld_corner);
    vec2d vessel_lu(vessel.ld_corner.x, vessel.ru_corner.y);
    vec2d vessel_ru(vessel.ru_corner);
    vec2d vessel_rd(vessel.ru_corner.x, vessel.ld_corner.y);

    for (size_t index = 0; index < moleculs.size; ++index)
    {
        molecule_t &cur_molecule = **cur_molecule_ptr;

//      printf("vessel_ld = {%lg, %lg}\n", vessel_ld.x, vessel_ld.y);
//      printf("vessel_lu = {%lg, %lg}\n", vessel_lu.x, vessel_lu.y);
//      printf("vessel_ru = {%lg, %lg}\n", vessel_ru.x, vessel_ru.y);
//      printf("vessel_rd = {%lg, %lg}\n", vessel_rd.x, vessel_rd.y);

//      printf("center_pos= {%lg, %lg}\n", cur_molecule.center.position.x, cur_molecule.center.position.y);

        bool is_hitted = cur_molecule.try_hit_piston (frame_time, piston);
        if (!is_hitted)  is_hitted = cur_molecule.try_hit_segment(frame_time, segment_t(vessel_ld, vessel_lu));
        if (!is_hitted)  is_hitted = cur_molecule.try_hit_segment(frame_time, segment_t(vessel_lu, vessel_ru));
        if (!is_hitted)  is_hitted = cur_molecule.try_hit_segment(frame_time, segment_t(vessel_ru, vessel_rd));
        if (!is_hitted)  is_hitted = cur_molecule.try_hit_segment(frame_time, segment_t(vessel_rd, vessel_ld));
        if (!is_hitted)  cur_molecule.refresh(frame_time);

        cur_molecule_ptr = (molecule_t **) list_next(&moleculs, cur_molecule_ptr);
    }

    piston.center.refresh(frame_time);
}
