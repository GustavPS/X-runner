#include "object.h"

Object::Object(const sf::Vector2f &position, const sf::Vector2f &dimensions, const std::string &name)
    : position { position }
    , dimensions { dimensions }
    , name { name }
    , shape { dimensions }
{
    shape.setPosition(position);
}