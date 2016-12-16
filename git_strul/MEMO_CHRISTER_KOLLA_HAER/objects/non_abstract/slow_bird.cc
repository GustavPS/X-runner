#include "slow_bird.h"

Slow_Bird::Slow_Bird(const sf::Vector2f &position,
                     const sf::Vector2f &size,
                     const std::string &type,
                     const sf::Texture *const texture,
                     const float speed,
                     const int direction)
    : Bird { position, size, type, texture, speed, direction, 2.f }
    // cooldown -----------------------------------------------^
{}