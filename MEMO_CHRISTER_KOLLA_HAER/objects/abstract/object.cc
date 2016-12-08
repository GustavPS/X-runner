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

sf::Vector2f Object::get_position() const
    { return position; }

sf::RectangleShape Object::get_shape() const
    { return shape; }

std::vector<std::string> Object::get_types() const
    { return types; }