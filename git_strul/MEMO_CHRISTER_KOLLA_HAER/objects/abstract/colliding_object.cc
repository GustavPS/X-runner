#include "colliding_object.h"

Colliding_Object::Colliding_Object(const sf::Vector2f &position,
                                   const sf::Vector2f &size,
                                   const std::string &type,
                                   const bool solid)
    : Simulatable { position, size, type, solid }
{}

void Colliding_Object::check_collision(const std::vector<const Object*> &objects,
                                       const sf::Vector2f &steps)
{
    std::vector<const Object*> colliding_objects;

    std::copy_if(
        objects.begin(),
        objects.end(),
        std::back_inserter(colliding_objects),
        [this](auto *object) {
            return shape.getGlobalBounds().intersects(
                object->get_shape().getGlobalBounds());
        }
    );

    for (auto *colliding_object : colliding_objects)
    {
        handle_collision(colliding_object, steps);
    }

    handle_end_collision(steps);
}

void Colliding_Object::end_simulate(const std::vector<const Object*> &objects)
{
    collision_state_cleanup();
    check_collision(objects);
}