#include "gravitable.h"

Gravitating_Object::Gravitating_Object(const sf::Vector2f &position,
                                       const sf::Vector2f &size,
                                       const std::vector<std::string> &types,
                                       float speed,
                                       float weight)
    : Movable_Object { position, size, types, speed }
    , weight { weight }
{}

int Gravitating_Object::prepare_simulate(const float distance_modifier,
                                         const float gravity_constant)
{
    // Apply gravity_constant
    distance.y += gravity_constant
                  * gravity_clock.getElapsedTime()
                        .asMilliseconds()
                  / 15;

    // Continue simulation
    // Return the number of simulations needed for this object
    return Movable_Object::prepare_simulate(distance_modifier);
}

void Gravitating_Object::simulate(const int total_simulations,
                                  std::vector<Object*>& objects)
{
    // Continue simulation
    Movable_Object::simulate(
        total_simulations, objects);
}

bool Gravitating_Object::handle_collision(Object *object, const sf::Vector2f &steps)
{
    bool has_collided { Movable_Object::handle_collision(object, steps) };

    const std::string _type { object->get_types().at(0) };

    if (_type == "ground" && steps.y > 0)
    {
        gravity_clock.restart();
        has_collided = true;
    }
    else if (_type == "roof" && steps.y < 0)
    {
        gravity_clock.restart(); // ?? VILL VI???
        has_collided = true;
    }
}