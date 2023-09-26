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
protected:
    rectangle_t area;

public:
    explicit button_t(const vec2d &pos_,
                      const vec2d &size_):
    area (pos_, pos_ + size_)
    {}

    virtual void draw   (sf::RenderTarget &wnd) const = 0;
    virtual void refresh(const vec2d &mouse_pos, const bool is_clicked) = 0;
    virtual void perform(molecule_manager_t &molecule_manager) const;
};

//--------------------------------------------------------------------------------------------------

class hold_button_t: public button_t
{
private:
    enum BUTTON_STATE_TYPE
    {
        BUTTON_PRESS,
        BUTTON_HOLD,
        BUTTON_RELEASE,
        BUTTON_OFF,
    }
    state;

    typedef void (*action_t) (molecule_manager_t &molecule_man);
    action_t action;
    vec2d    scale;

    static sf::Texture tex_on;
    static sf::Texture tex_off;

    static bool are_texs_init;
    static void texs_init();

public:
    explicit hold_button_t(const vec2d    &pos_,
                           const vec2d    &size_,
                           const action_t &action_);

    virtual void draw   (sf::RenderTarget &wnd) const override;
    virtual void refresh(const vec2d &mouse_pos, const bool is_clicked) override;
    virtual void perform(molecule_manager_t &molecule_manager) const override;
};

//--------------------------------------------------------------------------------------------------

class switch012_button_t: public button_t
{
private:
    enum BUTTON_STATE_TYPE
    {
        BUTTON_0,
        BUTTON_1,
        BUTTON_2,

        BUTTON_SWITCHED_TO_0,
        BUTTON_SWITCHED_TO_1,
        BUTTON_SWITCHED_TO_2,
    }
    state;

    typedef void (*action_t) (molecule_manager_t &molecule_man);
    action_t switched_0_action;
    action_t switched_1_action;
    action_t switched_2_action;

    static sf::Texture tex_0;
    static sf::Texture tex_1;
    static sf::Texture tex_2;

    static bool are_texs_init;
    static void texs_init();

public:
    explicit switch012_button_t(const vec2d &pos_,
                                const vec2d &size_,
                                const action_t &action_0,
                                const action_t &action_1,
                                const action_t &action_2);

    virtual void draw   (sf::RenderTarget &wnd) const override;
    virtual void refresh(const vec2d &mouse_pos, const bool is_clicked) override;
    virtual void perform(molecule_manager_t &molecule_manager) const override;
};

#endif // BUTTON_H
