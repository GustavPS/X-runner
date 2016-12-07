#ifndef PLAYER_H
#define PLAYER_H

#include "../abstract/gravitable.h"

class Player : public Gravitable
{
    public:
        // Constructors & destructors
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&,
               float,
               float);
               
        // Simulation
        void simulate(float,
                      float,
                      const std::vector<Object*>&) override;

    private:
        // State
        bool on_ground;
        bool on_quicksand;
        sf::Clock increase_speed_clock;
        sf::Clock decrease_speed_clock;
        sf::Clock nullify_speed_clock;

        // Collision handling
        void handle_collision(const std::string &type) override;
};

#endif