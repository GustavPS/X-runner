#include "gravitable.h"

Gravitating_Object::Gravitating_Object(const sf::Vector2f &position,
                                       const sf::Vector2f &size,
                                       const std::string &type,
                                       const bool solid)
    : Movable_Object { position, size, type, solid }
{}
#include <iostream>
int Gravitating_Object::prepare_simulate(const float distance_modifier,
                                         const float gravity_constant)
{
    /*std::cerr << gravity_clock.getElapsedTime()
                        .asMilliseconds() << "   ";*/

    float gravity_modifier { gravity_clock.getElapsedTime()
                                .asMilliseconds()
                             / 15.f };

    //std::cerr << gravity_modifier << "  ";

    // Apply gravity_constant
    distance.y += gravity_constant * gravity_modifier;

    //std::cerr << distance.y * distance_modifier << "     ";

    // Continue simulation
    // Return the number of simulations needed for this object
    return Movable_Object::prepare_simulate(distance_modifier);
}

void Gravitating_Object::handle_collision(const Object *object,
                                          const sf::Vector2f &steps)
{
    Movable_Object::handle_collision(object, steps);

    if (object->is_solid())
    {
        if (steps.y != 0.f)
        {
            gravity_clock.restart();
        }
    }
}