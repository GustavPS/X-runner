#include "movable.h"

#include <cmath>

Movable_Object::Movable_Object(const sf::Vector2f& position,
                               const sf::Vector2f& size,
                               const std::string &type,
                               const bool solid,
                               const sf::Texture *const texture)
    : Simulatable { position, size, type, solid, texture }
{}

int Movable_Object::prepare_simulate(const float distance_modifier)
{
    // Apply distance_modifier
    m_distance *= distance_modifier;

    // Calulate axis with the greatest movement
    float longest { std::abs(
                        std::abs(m_distance.x) > std::abs(m_distance.y)
                        ? m_distance.x
                        : m_distance.y) };

    // Calculate the number of simulations needed for this object
    // (an object can never move >24 (smallest object) on any axis per simulation)
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
    // Reset collision state
    collision_state_cleanup();

    // Check collisions before moving
    // (if another object collided with this whilst not moving)
    for (auto *colliding_object : get_colliding_objects(objects))
        handle_static_collision(colliding_object);

    sf::Vector2f steps;

    if (m_distance.x != 0)
    {
        // Move on x-axis, then check collision
        steps = { m_distance.x / total_simulations, 0.f };
        m_shape.setPosition(m_shape.getPosition() + steps);
        for (auto *colliding_object : get_colliding_objects(objects))
            handle_moving_collision(colliding_object, steps);
    }

    if (m_distance.y != 0)
    {
        // Move on y-axis, then check collision
        steps = { 0.f, m_distance.y / total_simulations };
        m_shape.setPosition(m_shape.getPosition() + steps);
        for (auto *colliding_object : get_colliding_objects(objects))
            handle_moving_collision(colliding_object, steps);
    }

    for (auto *colliding_object : get_colliding_objects(objects))
        handle_static_collision(colliding_object);

    handle_end_collision();

    return {};
}

void Movable_Object::end_simulate(const std::vector<const Object*> &objects)
{
    m_distance *= 0.f;
}

void Movable_Object::handle_moving_collision(const Object *object,
                                      const sf::Vector2f &steps)
{
    if (object->is_solid())
    {
        auto colliding_shape { object->get_shape() };

        if (steps.y > 0.f && !m_ground_collision)
        {
            m_shape.setPosition(m_shape.getPosition().x, colliding_shape.getPosition().y
                                                     - m_shape.getSize().y);
            m_ground_collision = true;
        }
        else if (steps.y < 0.f && !m_roof_collision)
        {
            m_shape.setPosition(m_shape.getPosition().x, colliding_shape.getPosition().y
                                                     + colliding_shape.getSize().y);
            m_roof_collision = true;
        }
        else if (steps.x < 0.f && !m_wall_collision)
        {
            m_shape.setPosition(colliding_shape.getPosition().x + colliding_shape.getSize().x
                            , m_shape.getPosition().y);
        }
        else if (steps.x > 0.f && !m_wall_collision)
        {
            m_shape.setPosition(colliding_shape.getPosition().x - m_shape.getSize().x
                            , m_shape.getPosition().y);
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