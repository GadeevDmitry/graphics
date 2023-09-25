#ifndef BUTTON_MANAGER_H
#define BUTTOM_MANAGER_H

#include "button.h"

#include "logs/log.h"
#include "vector/vector.h"

#include <SFML/Graphics.hpp>

//==================================================================================================

class button_manager_t
{
private:
    vector buttons;

public:
    button_manager_t()
    {
        vector_ctor(&buttons, sizeof(button_t));
    }

    ~button_manager_t()
    {
        vector_dtor(&buttons);
    }

    bool add_button(const button_t &button)
    {
        vector_push_back(&buttons, &button);
    }

    void draw(sf::RenderWindow &wnd)
    {
        for (size_t ind = 0; ind < buttons.size; ++ind)
            ((button_t *) vector_get(&buttons, ind))->draw(wnd);
    }

    void refresh(const vec2d &mouse_pos, const bool is_clicked)
    {
        for (size_t ind = 0; ind < buttons.size; ++ind)
            ((button_t *) vector_get(&buttons, ind))->refresh(mouse_pos, is_clicked);
    }
};

#endif // BUTTON_MANAGER_H
