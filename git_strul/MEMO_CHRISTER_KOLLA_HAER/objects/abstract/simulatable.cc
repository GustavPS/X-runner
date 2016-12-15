#include "simulatable.h"

Simulatable::Simulatable(const sf::Vector2f &position,
                         const sf::Vector2f &size,
                         const std::string &type,
                         const bool solid)
    : Object { position, size, type, solid }
{}