#ifndef BIRD_H
#define BIRD_H

#include "../abstract/movable.h"

class Bird : public Movable_Object
{
    public:
        // Constructors & destructors
        Bird(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::vector<std::string> &types,
             float);

        virtual int prepare_simulate(const float,
                                     const float) override final;

        // Execute simulation of object : overriding pure virtual : NOT final
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override;

    protected:
        // Attributes
        const float speed;

        // State : general
        float m_direction;

        // State : buffs & debuffs
        sf::Clock player_clock;
        bool player_debuff {};
        
        // Collision handling : overriding null-defined : final
        virtual bool handle_collision(const Object*,
                                      const sf::Vector2f&) override final;
};

#endif