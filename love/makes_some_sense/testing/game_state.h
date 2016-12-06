#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"

class Game_State : public State
{
    public:
        Game_State();
        void load_level();
        int simulate() override;
        void reset() override;
        sf::Clock clock;

    private:
        double gravity_modifier;
        Player *player;
        std::vector<Wall*> walls;
        std::vector<Ground*> grounds;
        std::vector<Roof*> roofs;
        std::vector<NPC*> npcs;
        std::vector<Gravitable*> gravitables;
}

#endif