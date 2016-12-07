#include "object.h"

Object::Object(const std::string &name, const sf::Vector2f &position, const sf::Vector2f &dimensions)
    : name { name }
    , position { position }
    , dimensions { dimensions }
    , shape { dimensions }
{
    shape.setPosition(position);
}

void Object::set_position(const sf::Vector2f &new_position)
{
    position = new_position;
    shape.setPosition(new_position);
}

std::string Object::get_name() const { return name; }
sf::Vector2f Object::get_position() const { return position; }
sf::Vector2f Object::get_dimensions() const { return dimensions; }
sf::RectangleShape Object::get_shape() const { return shape; }