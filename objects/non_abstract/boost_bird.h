#ifndef BOOST_BIRD_H
#define BOOST_BIRD_H

#include "../abstractish/bird.h"

class Boost_Bird final : public Bird
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor"
           \param position "Position of the object"
           \param size "Size of the object"
           \param type "Type of the object"
           \param texture "Texture of the object"
           \param speed "Speed of the object"
           \param direction "Direction of the object"
        */
        Boost_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const sf::Texture*,
                   const float,
                   const int);
};

#endif
