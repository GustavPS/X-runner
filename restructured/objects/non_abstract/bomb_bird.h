#ifndef BOMB_BIRD_H
#define BOMB_BIRD_H

#include "slow_bird.h"

class Bomb_Bird final : public Slow_Bird
{
    public:
        // Constructors & destructors
        Bomb_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const sf::Texture*,
                   const float,
                   const int,
                   const sf::Texture*);

        // Execute simulation of object : overriding defined : final
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override final;

    private:
        // Constants : textures
        const sf::Texture *m_nfbb_texture;

        // State : general
        sf::Clock m_nfbb_clock;
};

#endif