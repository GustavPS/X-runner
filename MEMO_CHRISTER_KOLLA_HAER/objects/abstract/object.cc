#include "object.h"

Object::Object(const sf::Vector2f &position,
               const sf::Vector2f &size,
               const std::string &type,
               const bool solid)
    : shape { size }
    , type { type }
    , solid { solid }
{
    shape.setPosition(position);
}

std::string Object::get_type() const
    { return type; }

bool Object::is_solid() const
    { return solid; }

bool Object::get_delete_status() const
    { return m_delete_status; }

sf::RectangleShape Object::get_shape() const
    { return shape; }