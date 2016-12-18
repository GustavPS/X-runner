#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../abstract/state.h"
#include "../../objects/abstractish/simulatable_object.h"
#include "../../objects/non_abstract/player.h"

class Game_State : public State
{
    public:
        // Constructors & destructors
        Game_State();

        // Simulation : overriding pure virtual
        void prepare_simulate() override;
        int simulate() override;

        // View : overriding pure virtual
        void set_view(sf::View&) override;

    private:
        // State
        float gravity_constant;
        sf::Clock delta_clock;
        sf::Clock result_clock;

        // Objects
        std::vector<Simulatable_Object*> simulatable_objects;
        const Player *player;

        // Reset : overriding defined
        void soft_reset() override;
};

#endif