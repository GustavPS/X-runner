#include "simulatable.h"

Simulatable::Simulatable(const sf::Vector2f &position,
                         const sf::Vector2f &dimensions,
                         const std::vector<std::string> &types)
    : Object { position, dimensions, types }
{}