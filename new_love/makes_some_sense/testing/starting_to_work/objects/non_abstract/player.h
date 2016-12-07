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
        bool on_ground {};
        bool on_quicksand {};
        int slow_bird_count {};
        int boost_bird_count {};
        sf::Clock slow_bird_clock;
        sf::Clock boost_bird_clock;
        sf::Clock nfbb_clock;

        // Collision handling
        void handle_collision(const std::string &type) override;
};

#endif