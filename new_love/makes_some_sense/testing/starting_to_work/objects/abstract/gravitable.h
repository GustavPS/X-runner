#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable.h"

class Gravitable : public Movable
{
    public:
        //constructors & destructors
        Gravitable(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   float);

    protected:
        void gravitate(float,
                       float,
                       const std::vector<Object*>&);
};

#endif