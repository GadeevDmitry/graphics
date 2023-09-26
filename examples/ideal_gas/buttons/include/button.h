#ifndef BUTTON_H
#define BUTTON_H

#include "vec2d.h"
#include "rectangle.h"

#include "logs/log.h"
#include "algorithm/algorithm.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class button_t
{
private:
    rectangle_t area;
    vec2d       scale;

    sf::Texture tex_on;
    sf::Texture tex_off;

    enum BUTTON_STATE_TYPE
    {
        BUTTON_ON   ,
        BUTTON_OFF  ,
    }
    state;

public:
    explicit button_t(const vec2d &position_,
                      const vec2d &size_,

                      const char *tex_on_file_,
                      const char *tex_off_file_);

    void draw   (sf::RenderTarget &wnd) const;
    void refresh(const vec2d &mouse_pos, const bool is_clicked);
};

#endif // BUTTON_H
