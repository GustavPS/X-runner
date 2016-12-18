#include "boost_bird.h"

Boost_Bird::Boost_Bird(const sf::Vector2f &position,
                       const sf::Vector2f &size,
                       const std::string &type,
                       const sf::Texture *texture,
                       const float speed,
                       const int direction)
    : Bird { position, size, type, texture, speed, direction, 2.25f }
    // cooldown -----------------------------------------------^
{}