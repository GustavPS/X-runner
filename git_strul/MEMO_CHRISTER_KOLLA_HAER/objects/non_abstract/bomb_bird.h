#ifndef BOMB_BIRD_H
#define BOMB_BIRD_H

#include "bird.h"

class Bomb_Bird final : public Bird
{
    public:
        // Constructors & destructors
        Bomb_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const float);

        // Execute simulation of object : overriding defined : final
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override final;

    private:
        // State : general
        sf::Clock nfbb_clock;
};

#endif