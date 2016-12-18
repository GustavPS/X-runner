#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "../abstract/state.h"
#include "../../objects/non_abstract/player.h"

class Menu_State : public State
{
    public:
        // Constructors & destructors
        Menu_State();

        // Simulation : overriding pure virtual
        void prepare_simulate() override;
        int simulate() override;

        // View : overriding pure virtual
        void set_view(sf::View&) override;

    private:
        // State
        float gravity_constant;
        sf::Clock delta_clock;

        // Objects
        Player *player;

        // Reset : overriding defined
        void soft_reset() override;
};

#endif