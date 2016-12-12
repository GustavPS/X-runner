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

        virtual int prepare_simulate(std::vector<Object*>&,
                                     const float,
                                     const float) override final;

        // Execute simulation of object : overriding pure virtual : final
        virtual void simulate(const int,
                              std::vector<Object*>&) override final;

    private:
        // State : general
        bool jumping {};
        bool on_ground {};

        // State : buffs & debuffs
        sf::Clock slow_bird_clock;
        std::unordered_set<Object*> slow_bird_debuffs;

        sf::Clock boost_bird_clock;
        std::unordered_set<Object*> boost_bird_buffs;

        sf::Clock nfbb_clock;
        bool nfbb_debuff {};

        bool quicksand_debuff {};

        // Collision handling : overriding null-defined : final
        virtual bool handle_collision(Object*, const sf::Vector2f&) override final;
        virtual void handle_end_collision(const sf::Vector2f &steps) override final;
};

#endif