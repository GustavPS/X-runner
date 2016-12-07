#ifndef SIMULATEABLE_H
#define SIMULATABLE_H

#include "object.h"

class Simulate : public Object
{
    public:
        // Constructors & destructors
        Simulate(const sf::Vector2f&,
                 const sf::Vector2f&,
                 const std::string&);
        // Pure virtual functions
        virtual void simulate(float,
                              float,
                              const std::vector<Object*>&) = 0;
};

#endif