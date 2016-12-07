#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable.h"

class Gravitable : public Movable
{
    public:
        // Constructors & destructors
        Gravitable(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
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