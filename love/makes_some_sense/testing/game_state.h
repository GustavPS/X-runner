#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"

class Game_State : public State
{
    public:
        Game_State();
        void load_level();
        int simulate() override;

    private:

}

#endif