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
        
        // Gravitation
        void gravitate(float,
                       float,
                       const std::vector<Object*>&);
};

#endif