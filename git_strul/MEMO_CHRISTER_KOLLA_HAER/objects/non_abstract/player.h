#ifndef PLAYER_H
#define PLAYER_H

#include "../abstract/gravitable.h"

#include <unordered_set>

class Player final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&,
               const float);

        // Prepare and calculate the required amount of simulations 
        // : overriding defined : final
        virtual int prepare_simulate(const float,
                                     const float) override final;

    private:
        // Constants : attributes
        const float speed;

        // State : general
        bool jumping {};
        bool on_ground {};

        // State : buffs & debuffs
        sf::Clock slow_bird_clock;
        std::unordered_set<const Object*> slow_bird_debuffs;

        sf::Clock boost_bird_clock;
        std::unordered_set<const Object*> boost_bird_buffs;

        sf::Clock nfbb_clock;
        bool nfbb_debuff {};

        bool quicksand_debuff {};

        // State : collision
        bool m_quicksand_collision {};

        // Collision handling : overriding defined : final
        virtual void handle_collision(const Object*, const sf::Vector2f&) override final;
        virtual void collision_state_cleanup() override final;

        // Collision handling : overriding null-defined : final
        virtual void handle_end_collision(const sf::Vector2f &steps) override final;
};

#endif