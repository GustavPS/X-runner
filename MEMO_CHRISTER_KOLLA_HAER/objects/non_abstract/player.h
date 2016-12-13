#ifndef PLAYER_H
#define PLAYER_H

#include "../abstract/gravitable.h"

class Player final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::vector<std::string> &types,
               float);

        virtual int prepare_simulate(const float,
                                     const float) override final;

    private:
        // Attributes
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

        // Collision handling : overriding null-defined : final
        virtual bool handle_collision(const Object*, const sf::Vector2f&) override final;
        virtual void handle_end_collision(const sf::Vector2f &steps) override final;
};

#endif