#include "movable.h"

#include <cmath>

Movable_Object::Movable_Object(const sf::Vector2f& position,
               const sf::Vector2f& dimensions,
               const std::vector<std::string> &types,
               float speed)
    : Simulatable { position, dimensions, types }
    , speed { speed }
{}

void Movable_Object::simulate(std::vector<Object*> &objects,
                              float distance_modifier,
                              sf::Vector2f &distance)
{
    distance *= distance_modifier;

    float &longest { std::abs(distance.x) > std::abs(distance.y)
                     ? distance.x
                     : distance.y };

    sf::Vector2f steps { distance.x / longest, distance.y / longest };
    sf::Vector2f partial_steps;

    for (int i {}; longest > 1; ++i)
    {
        if (i % 2 == 0)
        {
            partial_steps = { steps.x, 0 };
            set_position(position.x + steps.x, position.y);
        }
        else
        {
            partial_steps = { 0, steps.y };
            set_position(position.x, position.y + steps.y);
        }
        distance.x -= partial_steps.x;
        distance.y -= partial_steps.y;
        check_collision(objects, partial_steps);
    }

    partial_steps = { distance.x, 0 };
    set_position(position.x + distance.x, position.y);
    check_collision(objects, partial_steps);

    partial_steps = { 0, distance.y };
    set_position(position.x, position.y + distance.y);
    check_collision(objects, partial_steps);
}

#include <iostream>
void Movable_Object::check_collision(std::vector<Object*> &objects,
                                     const sf::Vector2f &steps)
{
    for (auto object : objects)
    {
        if (object->m_delete == false
         && shape.getGlobalBounds().intersects(
            object->get_shape().getGlobalBounds()))
        {
            if (handle_collision(object, steps))
                for (std::string &type : object->get_types())
                    collided_object_types.insert(type);
        }
    }
    handle_end_collision();
    collided_object_types.clear();
}

void Movable_Object::set_position(const sf::Vector2f &_position)
{
    position = _position;
    shape.setPosition(_position);
}

void Movable_Object::set_position(float x, float y)
{
    position.x = x;
    position.y = y;
    shape.setPosition(x, y);
}

bool Movable_Object::handle_collision(Object *object, const sf::Vector2f &steps)
{
    bool collision_occured {};
    std::string _type { object->get_types().at(0) };

    /*Collision with types*/
    if (_type == "ground" && steps.y > 0
     && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x, position.y - steps.y);
        collision_occured = true;
    }
    else if (_type == "roof" && steps.y < 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x, position.y - steps.y);
        collision_occured = true;
    }
    else if (_type == "wall" && steps.x != 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x - steps.x, position.y);
        collision_occured = true;
    }

    return collision_occured;
}