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

void increase_molecules_act(const button_t &button, molecule_manager_t &manager);
void decrease_molecules_act(const button_t &button, molecule_manager_t &manager);
void raise_piston_act      (const button_t &button, molecule_manager_t &manager);
void lower_piston_act      (const button_t &button, molecule_manager_t &manager);

//==================================================================================================

button_manager_t::button_manager_t(const vec2d &board_size_):
buttons_tex()
{
    log_verify(board_size_.x > 0, ;);
    log_verify(board_size_.y > 0, ;);

    array_ctor(&buttons, 4, sizeof(button_t *), delete_button);

    vec2d button_size = (board_size_ - (BOARD_LD_OFF + BOARD_RU_OFF)) / 2;

    vec2d ld_button_pos = BOARD_LD_OFF;
    vec2d rd_button_pos = BOARD_LD_OFF + vec2d(1 + button_size.x, 0);

    vec2d lu_button_pos = ld_button_pos + vec2d(0, 1 + button_size.y);
    vec2d ru_button_pos = rd_button_pos + vec2d(0, 1 + button_size.y);

    const char *button_on_tex  = "../../widget/img/button_on.png";
    const char *button_off_tex = "../../widget/img/button_off.png";

    button_t *more_molecules = new button_t(ld_button_pos, button_size, increase_molecules_act, button_on_tex, button_off_tex);
    button_t *less_molecules = new button_t(lu_button_pos, button_size, decrease_molecules_act, button_on_tex, button_off_tex);
    button_t *raise_piston   = new button_t(rd_button_pos, button_size, raise_piston_act      , button_on_tex, button_off_tex);
    button_t *lower_piston   = new button_t(ru_button_pos, button_size, lower_piston_act      , button_on_tex, button_off_tex);

    array_set(&buttons, 0, &more_molecules);
    array_set(&buttons, 1, &less_molecules);
    array_set(&buttons, 2, &raise_piston);
    array_set(&buttons, 3, &lower_piston);

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

void increase_molecules_act(const button_t &button, molecule_manager_t &manager)
{
    if (button.state == button_t::BUTTON_ON)
    {
        for (size_t ind = 0; ind < INCREASE_MOLECULE_UNIT; ++ind)
        {
            molecule_t *molecule = manager.create_light_molecule();
            vector_push_back(&manager.molecules, &molecule);
        }
    }
}

//--------------------------------------------------------------------------------------------------

void decrease_molecules_act(const button_t &button, molecule_manager_t &manager)
{
    if (button.state == button_t::BUTTON_ON)
    {
        int ind = manager.molecule_size <= DECREASE_MOLECULE_UNIT ? manager.molecule_size - 1 : DECREASE_MOLECULE_UNIT;
        for (; ind >= 0; --ind)
            vector_pop_back(&manager.molecules);
    }
}

//--------------------------------------------------------------------------------------------------

void raise_piston_act(const button_t &button, molecule_manager_t &manager)
{
    if (button.state == button_t::BUTTON_ON)      { manager.piston_speed = vec2d(0, -PISTON_SPEED); return; }
    if (button.state == button_t::BUTTON_RELEASE) { manager.piston_speed = vec2d(0, 0);             return; }
}

//--------------------------------------------------------------------------------------------------

void lower_piston_act(const button_t &button, molecule_manager_t &manager)
{
    if (button.state == button_t::BUTTON_ON)      { manager.piston_speed = vec2d(0, PISTON_SPEED); return; }
    if (button.state == button_t::BUTTON_RELEASE) { manager.piston_speed = vec2d(0, 0);            return; }
}
