#include "movable.h"

#include <cmath>

Movable_Object::Movable_Object(const sf::Vector2f& position,
                               const sf::Vector2f& size,
                               const std::string &type,
                               const bool solid)
    : Colliding_Object { position, size, type, solid }
{}

int Movable_Object::prepare_simulate(const float distance_modifier)
{
    // Apply distance_modifier
    distance *= distance_modifier;

    // Calulate axis with the greatest movement
    float longest { std::abs(
                        std::abs(distance.x) > std::abs(distance.y)
                        ? distance.x
                        : distance.y) };

    // Calculate the number of simulations needed for this object
    // (an object can never move >16 (smallest object) on any axis per simulation)
    int i {1};
    while (longest > 24.f)
    {
        longest -= 24;
        ++i;
    }

    // Return the number of simulations needed for this object
    return i;
}

std::vector<Object*> Movable_Object::simulate(const int total_simulations,
                                              const std::vector<const Object*> &objects)
{
    collision_state_cleanup();

    // Check collision before moving (if another object collided with this)
    check_collision(objects);

    // If there is movement
    if (distance.x != 0 || distance.y != 0)
    {
        // Move on x-axis, then check collision
        sf::Vector2f steps { distance.x / total_simulations, 0.f };
        shape.setPosition(shape.getPosition() + steps);
        check_collision(objects, steps);

        // Move on y-axis, then check collision
        steps = { 0.f, distance.y / total_simulations };
        shape.setPosition(shape.getPosition() + steps);
        check_collision(objects, steps);
    }

    return {};
}

void Movable_Object::end_simulate(const std::vector<const Object*> &objects)
{
    distance *= 0.f;
    Colliding_Object::end_simulate(objects);
}

void Movable_Object::handle_collision(const Object *object,
                                      const sf::Vector2f &steps)
{
    if (object->is_solid())
    {
        auto object_shape { object->get_shape() };

        if (steps.y > 0.f && !m_ground_collision)
        {
            shape.setPosition(shape.getPosition().x, object_shape.getPosition().y
                                                     - shape.getSize().y);
            m_ground_collision = true;
        }
        else if (steps.y < 0.f && !m_roof_collision)
        {
            shape.setPosition(shape.getPosition().x, object_shape.getPosition().y
                                                     + object_shape.getSize().y);
            m_roof_collision = true;
        }
        else if (steps.x < 0.f && !m_wall_collision)
        {
            shape.setPosition(object_shape.getPosition().x + object_shape.getSize().x
                            , shape.getPosition().y);
        }
        else if (steps.x > 0.f && !m_wall_collision)
        {
            shape.setPosition(object_shape.getPosition().x - shape.getSize().x
                            , shape.getPosition().y);
            m_wall_collision = true;
        }
    }
}

void Movable_Object::collision_state_cleanup()
{
    m_ground_collision = false;
    m_roof_collision = false;
    m_wall_collision = false;
}