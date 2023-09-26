#ifndef BUTTON_H
#define BUTTON_H

#include "vec2d.h"
#include "rectangle.h"

#include "logs/log.h"
#include "algorithm/algorithm.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

typedef class molecule_manager_t molecule_manager_t;

//--------------------------------------------------------------------------------------------------

class button_t
{
private:
    rectangle_t area;
    vec2d       scale;

    enum BUTTON_STATE_TYPE
    {
        BUTTON_ON,
        BUTTON_OFF,
        BUTTON_HOLD,
        BUTTON_RELEASE,
    }
    state;

    typedef void (*action_t) (const button_t &button, molecule_manager_t &molecule_man);
    action_t action;

    sf::Texture tex_on;
    sf::Texture tex_off;

public:
    explicit button_t(const vec2d   &position_,
                      const vec2d   &size_,
                      const action_t action_,

                      const char *tex_on_file_,
                      const char *tex_off_file_);

    void draw   (sf::RenderTarget &wnd) const;
    void refresh(const vec2d &mouse_pos, const bool is_clicked);
    void perform(molecule_manager_t &molecule_manager) const
    {
        action(*this, molecule_manager);
    }

    friend void increase_molecules_act(const button_t &button, molecule_manager_t &manager);
    friend void decrease_molecules_act(const button_t &button, molecule_manager_t &manager);
    friend void raise_piston_act      (const button_t &button, molecule_manager_t &manager);
    friend void lower_piston_act      (const button_t &button, molecule_manager_t &manager);
};

#endif // BUTTON_H
