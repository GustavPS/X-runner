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
             const sf::Texture *const,
             const float,
             const int,
             const float,
             const bool = false);

        // Prepare and calculate the required amount of simulations 
        // : overriding defined : final
        virtual int prepare_simulate(const float,
                                     const float) override final;

    protected:
        // Constants : Attributes
        const float m_speed;
        const float m_cooldown;

        // State : general
        int m_direction;

        // State : buffs & debuffs
        sf::Clock m_player_clock;
        bool m_player_debuff {};
        
        // Collision handling : overriding defined : final
        virtual void handle_moving_collision(const Object*,
                                      const sf::Vector2f&) override final;

        virtual void handle_static_collision(const Object*);
};

#endif