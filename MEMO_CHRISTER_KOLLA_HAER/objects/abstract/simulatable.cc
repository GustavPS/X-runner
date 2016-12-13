#include "simulatable.h"

Simulatable::Simulatable(const sf::Vector2f &position,
                         const sf::Vector2f &size,
                         const std::vector<std::string> &types)
    : Object { position, size, types }
{}

void Simulatable::check_collision(const std::vector<const Object*> &objects,
                                  const sf::Vector2f &steps,
                                  const bool clear)
{
    for (auto *object : objects)
    {
        if (!object->get_delete_status())
        {
            if (shape.getGlobalBounds().intersects(
                    object->get_shape().getGlobalBounds()))
            {
                if (handle_collision(object, steps))
                {
                    for (std::string &type : object->get_types())
                    {
                        collided_object_types.insert(type);
                    }
                }
            }
        }
    }
    handle_end_collision(steps);
    if (clear)
        collided_object_types.clear();
}

void Simulatable::end_simulate(const std::vector<const Object*> &objects)
{
    collided_object_types.clear();
    check_collision(objects);
}