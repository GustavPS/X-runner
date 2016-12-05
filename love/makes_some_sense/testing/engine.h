#ifndef ENGINE_H
#define ENGINE_H

#include "state.h"

class Engine
{
    public:
        Engine();
        void simulate();
        void render(sf::RenderWindow&);

    private:
        State* menu_state;
        State* game_state;
        State* active_state;
}

#endif