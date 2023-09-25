#ifndef SCENE_H
#define SCENE_H

#include "segment.h"
#include "rectangle.h"
#include "molecule_manager.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class scene_t
{
private:
    molecule_manager_t molecule_manager;

    segment_t   piston;
    rectangle_t walls;

    friend class molecule_manager_t;

public:
    explicit scene_t(const vec2d &area_size_);

    void draw   (sf::RenderTarget &wnd);
    void refresh(const double frame_time) { molecule_manager.refresh(frame_time, *this); }
};

#endif // SCENE_H
