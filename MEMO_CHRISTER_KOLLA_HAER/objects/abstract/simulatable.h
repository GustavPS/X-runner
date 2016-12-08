#ifndef SIMULATABLE_H
#define SIMULATABLE_H

#include "object.h"

class Simulatable : public Object
{
    public:
        // Constructors & destructors
        Simulatable(const sf::Vector2f&,
                 const sf::Vector2f&,
                 const std::vector<std::string>&);
        // Pure virtual functions
        virtual void simulate(float,
                              float,
                              std::vector<Object*>&) = 0;
};

#endif