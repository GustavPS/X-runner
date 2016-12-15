#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable.h"

class Gravitating_Object : public Movable_Object
{
    public:
        // Constructors & destructors
        Gravitating_Object(const sf::Vector2f&,
                           const sf::Vector2f&,
                           const std::string&,
                           const bool = false);

        // Prepare and calculate the required amount of simulations 
        // : overriding defined
        int prepare_simulate(const float,
                             const float);

    protected:
        // State : general
        sf::Clock gravity_clock;

        // Collision handling : overriding defined
        virtual void handle_collision(const Object*,
                                      const sf::Vector2f&) override;
};

#endif