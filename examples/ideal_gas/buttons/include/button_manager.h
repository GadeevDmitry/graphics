#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "button.h"

#include "logs/log.h"
#include "array/array.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class button_manager_t
{
private:
    array             buttons;
    sf::RenderTexture buttons_tex;

    static void delete_button(void *const button)
    {
        delete *(button_t **) button;
    }

public:
    explicit button_manager_t(const vec2d &board_size_);
    ~button_manager_t() { array_dtor(&buttons); }

    const sf::Texture &get_texture() const { return buttons_tex.getTexture(); }

    void draw();
    void refresh(const vec2d &mouse_pos, const bool is_clicked);
};

#endif // BUTTON_MANAGER_H
