#ifndef SLOW_BIRD_H
#define SLOW_BIRD_H

#include "../abstractish/bird.h"

class Slow_Bird : public Bird
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
           \param nfbb_texture "Texture of NFBB-objects spawned by the object"
        */
        Slow_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const sf::Texture*,
                   const float,
                   const int);
};

#endif
