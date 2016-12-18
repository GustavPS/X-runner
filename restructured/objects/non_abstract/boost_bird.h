#ifndef BOOST_BIRD_H
#define BOOST_BIRD_H

#include "../abstractish/bird.h"

class Boost_Bird final : public Bird
{
    public:
        // Constructors & destructors
        Boost_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const sf::Texture*,
                   const float,
                   const int);
};

#endif