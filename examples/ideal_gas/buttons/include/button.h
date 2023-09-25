#ifndef BUTTON_H
#define BUTTON_H

#include "vec2d.h"
#include "rectangle.h"

#include "logs/log.h"
#include "algorithm/algorithm.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

enum BUTTON_STATE_TYPE
{
    BUTTON_ON   ,
    BUTTON_OFF  ,
};

//--------------------------------------------------------------------------------------------------

class button_t
{
private:
    rectangle_t shape;
    vec2d       scale;

    sf::Texture tex_on;
    sf::Texture tex_off;

    BUTTON_STATE_TYPE state;

public:
    explicit button_t(const vec2d &pos_   = vec2d(),
                      const vec2d &size_  = vec2d(),
                      const vec2d &scale_ = vec2d(),

                      const sf::Texture &tex_on_  = sf::Texture(),
                      const sf::Texture &tex_off_ = sf::Texture()):
    shape(pos_, pos_ + size_),
    scale(scale_),

    tex_on (tex_on_),
    tex_off(tex_off_),

    state(BUTTON_OFF)
    {
        log_verify(dblcmp(pos_.x, 0) >= 0, ;);
        log_verify(dblcmp(pos_.y, 0) >= 0, ;);

        log_verify(dblcmp(size_.x, 0) >= 0, ;);
        log_verify(dblcmp(size_.y, 0) >= 0, ;);

        log_verify(dblcmp(scale_.x, 0) >= 0, ;);
        log_verify(dblcmp(scale_.y, 0) >= 0, ;);
    }

    void set_tex_on (const sf::Texture &tex_on_ ) { tex_on  = tex_on_;  }
    void set_tex_off(const sf::Texture &tex_off_) { tex_off = tex_off_; }
    void set_scale  (const vec2d scale_)          { scale   = scale_; }

    void draw   (sf::RenderWindow &wnd);
    void refresh(const vec2d &mouse_pos, const bool is_clicked);
};

#endif // BUTTON_H
