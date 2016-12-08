#ifndef PLAYER_H
#define PLAYER_H

#include "../abstract/gravitable.h"

class Player : public Gravitable
{
    public:
        // Constructors & destructors
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::vector<std::string> &types,
               float,
               float);

        // Simulation
        void simulate(float,
                      float,
                      std::vector<Object*>&) override;

    private:
        // State
        int jump_steps {};
        bool should_accelerate_jump {};
        bool on_ground {};
        bool on_quicksand {};
        int slow_bird_count {};
        int boost_bird_count {};
        sf::Clock slow_bird_clock;
        sf::Clock boost_bird_clock;
        sf::Clock nfbb_clock;

        // Collision handling
        void handle_collision(Object*&, const sf::Vector2f&) override;
        void handle_end_collision() override;
        void handle_null_collision() override;

        // Helpers
        void accelerate_jump();
};

#endif