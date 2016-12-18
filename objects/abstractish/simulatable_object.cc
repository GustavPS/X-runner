#include "simulatable_object.h"

Simulatable_Object::Simulatable_Object(const sf::Vector2f &position,
                         const sf::Vector2f &size,
                         const std::string &type,
                         const bool solid,
                         const sf::Texture *texture)
    : Object { position, size, type, solid, texture }
{}

const std::vector<const Object*> Simulatable_Object::get_colliding_objects(
    const std::vector<const Object*> &objects) const
{
    std::vector<const Object*> colliding_objects;

    std::copy_if(
        objects.begin(),
        objects.end(),
        std::back_inserter(colliding_objects),
        [this](auto *object) {
            return m_shape.getGlobalBounds().intersects(
                object->get_shape().getGlobalBounds());
        }
    );

    return colliding_objects;
}