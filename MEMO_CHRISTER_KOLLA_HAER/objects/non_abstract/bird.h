#ifndef BIRD_H
#define BIRD_H

#include "../abstract/movable.h"

class Bird : public Movable_Object
{
    public:
        // Constructors & destructors
        Bird(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::string&,
             const float);

        // Prepare and calculate the required amount of simulations 
        // : overriding defined : final
        virtual int prepare_simulate(const float,
                                     const float) override final;

    protected:
        // Attributes
        const float speed;

        // State : general
        float m_direction;

        // State : buffs & debuffs
        sf::Clock player_clock;
        bool player_debuff {};
        
        // Collision handling : overriding defined : final
        virtual void handle_collision(const Object*,
                                      const sf::Vector2f&) override final;
};

#endif