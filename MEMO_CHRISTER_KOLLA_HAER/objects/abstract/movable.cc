#include "movable.h"

#include <cmath>

Movable_Object::Movable_Object(const sf::Vector2f& position,
                               const sf::Vector2f& size,
                               const std::vector<std::string> &types)
    : Simulatable { position, size, types }
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
    // (an object can never move >1 on any axis per simulation)
    int i {1};
    while (longest-- > 1)
        ++i;

    // Return the number of simulations needed for this object
    return i;
}

std::vector<Object*> Movable_Object::simulate(const int total_simulations,
                                              const std::vector<const Object*> &objects)
{
    // Check collision before moving (if another object collided with this)
    check_collision(objects);

    // Move on x-axis, then check collision
    sf::Vector2f steps { distance.x / total_simulations, 0 };
    shape.setPosition(shape.getPosition() + steps);
    check_collision(objects, steps, false);

    // Move on y-axis, then check collision
    steps = { 0, distance.y / total_simulations };
    shape.setPosition(shape.getPosition() + steps);
    check_collision(objects, steps);

    return {};
}

void Movable_Object::end_simulate(const std::vector<const Object*> &objects)
{
    distance *= 0.f;
    Simulatable::end_simulate(objects);
}

bool Movable_Object::handle_collision(const Object *object,
                                      const sf::Vector2f &steps)
{
    bool has_collided {};
    
    const std::string _type { object->get_types().at(0) };

    if (_type == "ground" && steps.y > 0)
    {
        if (collided_object_types.find(_type)
            == collided_object_types.end())
        {
            shape.setPosition(shape.getPosition() - steps);
            has_collided = true;
        }
    }
    else if (_type == "roof" && steps.y < 0)
    {
        if (collided_object_types.find(_type)
            == collided_object_types.end())
        {
            shape.setPosition(shape.getPosition() - steps);
            has_collided = true;
        }
    }
    else if (_type == "wall" && steps.x != 0)
    {
        if (collided_object_types.find(_type)
            == collided_object_types.end())
        {
            shape.setPosition(shape.getPosition() - steps);
            has_collided = true;
        }
    }

    return has_collided;
}