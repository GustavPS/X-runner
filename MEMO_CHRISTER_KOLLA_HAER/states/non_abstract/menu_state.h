#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "../abstract/state.h"

#include <string>

class Menu_State : public State
{
    public:
        // Constructors & destructors
        ~Menu_State() noexcept;

        // Simulation
        int simulate() override;

    private:
        // Resetting the state
        void reset() override;
};

#endif