#ifndef ENGINE_H
#define ENGINE_H

//#include "states/non_abstract/menu_state.h"
#include "states/non_abstract/game_state.h"

class Engine
{
    public:
        Engine();
        void simulate();
        void render(sf::RenderWindow&);

    private:
        //State* menu_state;
        State* game_state;
        State* active_state;
        sf::View view;
};

#endif