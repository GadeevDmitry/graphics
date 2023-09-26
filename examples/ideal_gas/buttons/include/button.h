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
        BUTTON_ON   ,
        BUTTON_OFF  ,
        BUTTON_HOLD ,
    }
    state;

    typedef void (*action_t) (molecule_manager_t &molecule_manager);
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
        if (state == BUTTON_ON)
            action(molecule_manager);
    }
};

#endif // BUTTON_H
