#include <stdio.h>
#include <stdlib.h>

#include "button_manager.h"
#include "molecule_manager.h"

//==================================================================================================

static const vec2d BOARD_LD_OFF(5, 5);
static const vec2d BOARD_RU_OFF(5, 5);

//--------------------------------------------------------------------------------------------------

void increase_molecules_num(molecule_manager_t &manager);
void decrease_molecules_num(molecule_manager_t &manager);

//==================================================================================================

button_manager_t::button_manager_t(const vec2d &board_size_):
buttons_tex()
{
    log_verify(board_size_.x > 0, ;);
    log_verify(board_size_.y > 0, ;);

    array_ctor(&buttons, 2, sizeof(button_t *), delete_button);

    vec2d button_size(board_size_.x - (BOARD_LD_OFF.x + BOARD_RU_OFF.x),
                     (board_size_.y - (BOARD_LD_OFF.y + BOARD_RU_OFF.y)) / 2);

    button_t *more_molecules = new button_t(BOARD_LD_OFF, button_size,
                                            increase_molecules_num,
                                            "../../widget/img/button_on.png",
                                            "../../widget/img/button_off.png");

    button_t *less_molecules = new button_t(BOARD_LD_OFF + vec2d(0, 1 + button_size.y), button_size,
                                            decrease_molecules_num,
                                            "../../widget/img/button_on.png",
                                            "../../widget/img/button_off.png");

    array_set(&buttons, 0, &more_molecules);
    array_set(&buttons, 1, &less_molecules);

    buttons_tex.create((unsigned) board_size_.x, (unsigned) board_size_.y);
}

//--------------------------------------------------------------------------------------------------

void button_manager_t::draw()
{
    buttons_tex.clear();

    for (button_t **button = (button_t **) array_begin(&buttons);
                    button != array_end(&buttons);
                  ++button)
    {
        (*button)->draw(buttons_tex);
    }

    buttons_tex.display();
}

//--------------------------------------------------------------------------------------------------

void button_manager_t::refresh(const vec2d &mouse_pos, const bool is_clicked)
{
    for (button_t **button = (button_t **) array_begin(&buttons);
                    button != array_end(&buttons);
                  ++button)
    {
        (*button)->refresh(mouse_pos, is_clicked);
    }
}

//--------------------------------------------------------------------------------------------------

void button_manager_t::perform(molecule_manager_t &molecule_manager)
{
    for (button_t **button = (button_t **) array_begin(&buttons);
                    button != array_end(&buttons);
                  ++button)
    {
        (*button)->perform(molecule_manager);
    }
}

//--------------------------------------------------------------------------------------------------

void increase_molecules_num(molecule_manager_t &manager)
{
    molecule_t *molecule = manager.create_light_molecule();
    vector_push_back(&manager.molecules, &molecule);
}

//--------------------------------------------------------------------------------------------------

void decrease_molecules_num(molecule_manager_t &manager)
{
    if (manager.molecules.size == 0) return;
    vector_pop_back(&manager.molecules);
}
