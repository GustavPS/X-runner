#include "object.h"

Object::Object(const sf::Vector2f &position,
               const sf::Vector2f &size,
               const std::vector<std::string> &types)
    : position { position }
    , shape { size }
    , types {types}
    , m_interactable_status { true }
{
    shape.setPosition(position);
}

sf::Vector2f Object::get_position() const
    { return position; }

sf::RectangleShape Object::get_shape() const
    { return shape; }

std::vector<std::string> Object::get_types() const
    { return types; }

bool Object::get_delete_status() const
    { return m_delete_status; }