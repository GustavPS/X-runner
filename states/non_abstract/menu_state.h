#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "../abstract/state.h"
#include "../../objects/non_abstract/player.h"

class Menu_State : public State
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor : loads all textures and fonts used in the state"
        */
        Menu_State();

        // Simulation
        /*!
           \brief "Resets the state and loads a new level into it with the help
                   of the Level Parser class"
        */
        void prepare_simulate() override;
        /*!
           \brief "Simulates each object in the state and performs actions on
                   the state based on the result of the simulations"
           \return "An integer representing the next action to be taken by the Engine object"
        */
        int simulate() override;

        // View
        /*!
           \brief "Centers the view around the player"
           \param view "View to perform action on"
        */
        void set_view(sf::View&) override;

    private:
        // State
        float gravity_constant;
        sf::Clock delta_clock;

        // Objects
        Player *player;

        // Reset : overriding defined
        /*!
           \brief "Reset the game state."
        */
        void soft_reset() override;
};

#endif
