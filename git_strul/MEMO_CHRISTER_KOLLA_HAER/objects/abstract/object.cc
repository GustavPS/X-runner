#include "object.h"

Object::Object(const sf::Vector2f &position,
               const sf::Vector2f &size,
               const std::string &type,
               const bool solid,
               const sf::Texture *const texture)
    : m_shape { size }
    , m_type { type }
    , m_solid { solid }
    , m_texture { texture }
{
    m_shape.setPosition(position);
    if (m_texture != nullptr)
        m_shape.setTexture(m_texture);
}

std::string Object::get_type() const
    { return m_type; }

bool Object::is_solid() const
    { return m_solid; }

bool Object::get_delete_status() const
    { return m_delete_status; }

sf::RectangleShape Object::get_shape() const
    { return m_shape; }