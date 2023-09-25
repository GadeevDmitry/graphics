#ifndef SCENE_H
#define SCENE_H

#include "molecule_manager.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class scene_t
{
private:
    molecule_manager_t molecule_manager;

public:
    explicit scene_t(const vec2d &area_size_);

    void draw   (sf::RenderTarget &wnd);
    void refresh(const double frame_time) { molecule_manager.refresh(frame_time); }
};

#endif // SCENE_H
