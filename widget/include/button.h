#ifndef BUTTON_H
#define BUTTON_H

#include "vec2d.h"

#include "array/array.h"
#include <SFML/Graphics.hpp>

//==================================================================================================

class button_t
{
private:
    array textures;

public:
    vec2d  position;
    unsigned x_size;
    unsigned y_size;
    size_t    state;

    explicit button_t(const size_t texture_num_,
                      const char **texture_files_,

                      const vec2d &position_ = vec2d(),
                      const unsigned x_size_ = 0,
                      const unsigned y_size_ = 0,
                      const size_t    state_ = 0):
    position(position_),
    x_size  (x_size_),
    y_size  (y_size_),
    state   (state_)
    {
        array_ctor(textures, texture_num_, sizeof(sf::Texture));

        for (size_t ind = 0; ind < texture_num_; ++ind)
        {
            sf::Texture cur_tex;
            cur_tex.loadFromFile(texture_files_[ind]);

            array_set(&textures, ind, &cur_tex);
        }
    }

    ~button_t()
    {
        array_dtor(&textures);
    }

    void draw(sf::RenderWindow &wnd)
    {
        sf::Texture tex = *(sf::Texture *) array_get(&textures, state);
        sf::Sprite  spr(tex);
    }
};

#endif // BUTTON_H
