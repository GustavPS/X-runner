#ifndef SLOW_BIRD_H
#define SLOW_BIRD_H

#include "../abstractish/bird.h"

class Slow_Bird : public Bird
{
    public:
        // Constructors & destructors
        Slow_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const sf::Texture*,
                   const float,
                   const int);
};

#endif