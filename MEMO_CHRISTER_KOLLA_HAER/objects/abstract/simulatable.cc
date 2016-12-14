#include "simulatable.h"

Simulatable::Simulatable(const sf::Vector2f &position,
                         const sf::Vector2f &size,
                         const std::string &type,
                         const bool solid)
    : Object { position, size, type, solid }
{}

void Simulatable::check_collision(const std::vector<const Object*> &objects,
                                  const sf::Vector2f &steps)
{

    std::vector<const Object*> colliding_objects;
    for (auto *object : objects)
    {
        if (shape.getGlobalBounds().intersects(
                    object->get_shape().getGlobalBounds()))
        {
            colliding_objects.push_back(object);
        }
    }
    for (auto *colliding_object : colliding_objects)
    {
        handle_collision(colliding_object, steps);
    }
    handle_end_collision(steps);
}

void Simulatable::end_simulate(const std::vector<const Object*> &objects)
{
    collision_state_cleanup();
    check_collision(objects);
}