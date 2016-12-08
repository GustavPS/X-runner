#include "object.h"

Object::Object(const sf::Vector2f &position,
               const sf::Vector2f &dimensions,
               const std::vector<std::string> &types)
    : position { position }
    , shape { dimensions }
    , types {types}
{
    shape.setPosition(position);
}

sf::RectangleShape get_shape() const
    { return shape; }

std::vector<std::string> get_types() const
    { return types; }