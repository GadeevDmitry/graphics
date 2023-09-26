#include <stdio.h>
#include <stdlib.h>

#include "button_manager.h"
#include "molecule_manager.h"

//==================================================================================================

static const vec2d BOARD_LD_OFF(5, 5);
static const vec2d BOARD_RU_OFF(5, 5);

static const int INCREASE_MOLECULE_UNIT = 5;
static const int DECREASE_MOLECULE_UNIT = 5;
static const int PISTON_SPEED           = 100;

//--------------------------------------------------------------------------------------------------

void increase_molecules_act(molecule_manager_t &manager);
void decrease_molecules_act(molecule_manager_t &manager);

void raise_piston_act      (molecule_manager_t &manager);
void lower_piston_act      (molecule_manager_t &manager);
void stop_piston_act       (molecule_manager_t &manager);

//==================================================================================================

button_manager_t::button_manager_t(const vec2d &board_size_):
buttons_tex()
{
    log_verify(board_size_.x > 0, ;);
    log_verify(board_size_.y > 0, ;);

    array_ctor(&buttons, 3, sizeof(button_t *), delete_button);

    vec2d unit_size((board_size_.x - (BOARD_LD_OFF.x + BOARD_RU_OFF.x)) / 2,
                    (board_size_.y - (BOARD_RU_OFF.y + BOARD_RU_OFF.y)) / 3);

    vec2d l_button_pos = BOARD_LD_OFF;
    vec2d l_button_size(unit_size.x, 3*unit_size.y);

    vec2d rd_button_pos = BOARD_LD_OFF  + vec2d(unit_size.x + 1, 0);
    vec2d ru_button_pos = rd_button_pos + vec2d(0, unit_size.y + 1);

    button_t *piston_control = new switch012_button_t( l_button_pos, l_button_size, stop_piston_act, raise_piston_act, lower_piston_act);
    button_t *more_molecules = new press_button_t    (rd_button_pos,     unit_size, increase_molecules_act);
    button_t *less_molecules = new press_button_t    (ru_button_pos,     unit_size, decrease_molecules_act);

    array_set(&buttons, 0, &more_molecules);
    array_set(&buttons, 1, &less_molecules);
    array_set(&buttons, 2, &piston_control);

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

void increase_molecules_act(molecule_manager_t &manager)
{
    for (size_t ind = 0; ind < INCREASE_MOLECULE_UNIT; ++ind)
    {
        molecule_t *molecule = manager.create_light_molecule();
        vector_push_back(&manager.molecules, &molecule);
    }
}

//--------------------------------------------------------------------------------------------------

void decrease_molecules_act(molecule_manager_t &manager)
{
    int ind = manager.molecules.size <= DECREASE_MOLECULE_UNIT ?
              manager.molecules.size - 1 : DECREASE_MOLECULE_UNIT;

    for (; ind >= 0; --ind)
        vector_pop_back(&manager.molecules);
}

//--------------------------------------------------------------------------------------------------

void raise_piston_act(molecule_manager_t &manager) { manager.piston_speed = vec2d(0, -PISTON_SPEED); }
void lower_piston_act(molecule_manager_t &manager) { manager.piston_speed = vec2d(0,  PISTON_SPEED); }
void  stop_piston_act(molecule_manager_t &manager) { manager.piston_speed = vec2d(0, 0); }
