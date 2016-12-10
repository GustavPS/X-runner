#ifndef PLAYER_H
#define PLAYER_H

#include "../abstract/gravitable.h"

class Player : public Gravitating_Object
{
    public:
        // Constructors & destructors
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::vector<std::string> &types,
               float,
               float);

        // Simulation
        void simulate(std::vector<Object*>&,
                      float,
                      float) override;

    private:
        // State
        bool jumping {};
        bool on_ground {};
        bool on_quicksand {};
        int slow_bird_count {};
        int boost_bird_count {};
        int nfbb_count {};
        sf::Clock slow_bird_clock;
        sf::Clock boost_bird_clock;
        sf::Clock nfbb_clock;

        // Collision handling
        bool handle_collision(Object*, const sf::Vector2f&) override;
        void handle_end_collision() override;
};

#endif