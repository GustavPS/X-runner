#include "object.h"

Object::Object(const sf::Vector2f &position,
               const sf::Vector2f &dimensions,
               const std::string &type,
               const std::string &subtype)
    : position { position }
    , shape { dimensions }
    , type { type }
    , subtype { subtype }
{
    shape.setPosition(position);
}

sf::RectangleShape get_shape() const
    { return shape; }

std::string get_type() const
    { return type; }

std::string get_subtype() const
    { return subtype; }