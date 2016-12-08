#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable.h"

class Gravitable : public Movable
{
    public:
        // Constructors & destructors
        Gravitable(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::vector<std::string> &types,
                   float,
                   float);

    protected:
        // Attributes
        float weight;
        int count {};
        // Gravitation
        void simulate(float,
                       float,
                       std::vector<Object*>&) override;
};

#endif