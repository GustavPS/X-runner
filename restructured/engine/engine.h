#ifndef ENGINE_H
#define ENGINE_H

#include "../states/non_abstract/menu_state.h"
#include "../states/non_abstract/game_state.h"

class Engine
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor : creates State-objects and view,
                   as well as setting the active-state and prepares it for simulation"
        */
        Engine();
        /*!
           \brief "Destructor : frees resources owned by the Engine"
        */
        ~Engine();
        /*!
           \brief "Simulates the active state, and, depending on the return value
                  from the simulation, might change the active-state or close the window"
           \param window "window to close"
        */
        void simulate(sf::RenderWindow&);
        /*!
           \brief "draws all texturated objects and text objects in the active state"
           \param window "window draw on"
        */
        void render(sf::RenderWindow&);

    private:
        State* menu_state;
        State* game_state;
        State* active_state;
        sf::View view;
        //Record_Tracker record_tracker;
};

#endif
