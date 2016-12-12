#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable.h"

class Gravitating_Object : public Movable_Object
{
    public:
        // Constructors & destructors
        Gravitating_Object(const sf::Vector2f&,
                           const sf::Vector2f&,
                           const std::vector<std::string> &types,
                           float,
                           float);

        int prepare_simulate(const float,
                             const float);

        // Execute simulation of object : NOT overriding pure virtual
        void simulate(const int,
                      std::vector<Object*>&);
    protected:
        // State
        float weight;
        sf::Clock gravity_clock;

        // Collision handling : overriding null-defined
        virtual bool handle_collision(Object*, const sf::Vector2f&) override;
};

#endif