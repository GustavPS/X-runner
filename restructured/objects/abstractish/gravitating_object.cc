#include "gravitating_object.h"

Gravitating_Object::Gravitating_Object(const sf::Vector2f &position,
                                       const sf::Vector2f &size,
                                       const std::string &type,
                                       const bool solid,
                                       const sf::Texture *texture)
    : Movable_Object { position, size, type, solid, texture }
{}

int Gravitating_Object::prepare_simulate(const float distance_modifier,
                                         const float gravity_constant)
{
    float gravity_modifier { m_gravity_clock.getElapsedTime()
                                .asMilliseconds()
                             / 15.f };
    // -------------------------^
    // some awesome constant which gave smooth gravity
    // (there is probably some cool math to explain it)

    // Apply gravity_constant with gravity_modifier
    m_distance.y += gravity_constant * gravity_modifier;

    // Continue simulation
    // Return the number of simulations needed for this object
    return Movable_Object::prepare_simulate(distance_modifier);
}

void Gravitating_Object::handle_moving_collision(const Object *object,
                                          const sf::Vector2f &steps)
{
    Movable_Object::handle_moving_collision(object, steps);

    if (object->is_solid())
    {
        if (steps.y != 0.f)
        {
            m_gravity_clock.restart();
        }
    }
}