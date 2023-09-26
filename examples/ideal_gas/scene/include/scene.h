#ifndef SCENE_H
#define SCENE_H

#include "button_manager.h"
#include "molecule_manager.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class scene_t
{
private:
    molecule_manager_t molecule_manager;
    vec2d reactor_offset;

    button_manager_t button_manager;
    vec2d board_offset;

public:
    explicit scene_t(const vec2d &area_size_);

    void draw   (sf::RenderTarget &wnd);
    void refresh(const double frame_time, const vec2d &mouse_pos, const bool is_clicked)
    {
        button_manager.refresh(mouse_pos - board_offset, is_clicked);
        button_manager.perform(molecule_manager);

        molecule_manager.refresh(frame_time);
    }
};

#endif // SCENE_H
