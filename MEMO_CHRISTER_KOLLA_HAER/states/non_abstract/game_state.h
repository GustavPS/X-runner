#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../abstract/state.h"
#include "../../objects/abstract/simulatable.h"
#include "../../objects/non_abstract/player.h"
#include "../../level_parser/level_parser.h"

#include <string>

class Game_State : public State
{
    public:
        // Constructors & destructors
        ~Game_State() noexcept;

        // Loaders
        void load_level(const std::string &level);

        // Simulation
        int simulate() override;

        // State
        sf::Clock clock;

        //View
        void set_zoom(sf::View&) override;
        void set_view(sf::View&) override;

    private:
        // State
        float gravity_constant;

        // Objects
        std::vector<Simulatable*> simulatable_objects;
        Player *player;

        // Resetting the state
        void reset() override;
};

#endif