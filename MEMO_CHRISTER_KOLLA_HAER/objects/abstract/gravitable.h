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

    protected:
        // Attributes
        float weight;
        sf::Clock gravity_clock;
        // Gravitation
        void simulate(std::vector<Object*>&,
                      float,
                      float,
                      sf::Vector2f&);

        virtual bool handle_collision(Object*, const sf::Vector2f&) override;
};

#endif