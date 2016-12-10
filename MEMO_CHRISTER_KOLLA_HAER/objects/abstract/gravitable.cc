#include "gravitable.h"

Gravitating_Object::Gravitating_Object(const sf::Vector2f &position,
                                       const sf::Vector2f &dimensions,
                                       const std::vector<std::string> &types,
                                       float speed,
                                       float weight)
    : Movable_Object { position, dimensions, types, speed }
    , weight { weight }
{}

void Gravitating_Object::simulate(std::vector<Object*>& objects,
                                  float distance_modifier,
                                  float gravity_constant,
                                  sf::Vector2f &distance)
{
    // Apply gravity
    distance.y += gravity_constant
                  * gravity_clock.getElapsedTime()
                        .asMilliseconds()
                  / 15;

    // Continue simulation
    Movable_Object::simulate(objects, distance_modifier, distance);
}

bool Gravitating_Object::handle_collision(Object *object, const sf::Vector2f &steps)
{
    bool has_collided { Movable_Object::handle_collision(object, steps) };

    std::string _type { object->get_types().at(0) };

    /*Collision with types*/
    if (_type == "ground" && steps.y > 0
     && collided_object_types.find(_type) == collided_object_types.end())
    {
        gravity_clock.restart();
        has_collided = true; //kan omittas pga Movable_Object::this_fun
    }
    else if (_type == "roof" && steps.y < 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        gravity_clock.restart();
        has_collided = true; //kan omittas pga Movable_Object::this_fun
    }
}