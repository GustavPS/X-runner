#include "movable.h"

Player::Player(const sf::Vector2f& position,
               const sf::Vector2f& dimensions,
               const std::vector<std::string> &types,
               float speed)
    : Simulatable { position, dimensions, types }
    , speed { speed }
{}

void Movable::move(const sf::Vector2f &distance,
                   const std::vector<Object*> &objects)
{
    float longest& { distance.x > distance.y ? distance.x : distance.y };

    sf::Vector2f steps { distance.x / longest, distance.y / longest };

    while (longest > 1)
    {
        set_position(position.x + steps.x, position.y + steps.y);
        distance.x -= steps.x;
        distance.y -= steps.y;
        check_collision(steps, objects);
    }
    set_position(position.x + distance.x, position.y + distance.y);
    check_collision(steps, objects);
}

void Moveable::check_collision(const sf::Vector2f &steps)
                               const std::vector<Object*> &objects)
{
    for (auto it { objects.begin() }; it != objects.end(); ++it)
    {
        if (*it == nullptr)
        {
            objects.erase(it);
        }
        else if (shape.getGlobalBounds().intersects(
            (*it)->shape.getGlobalBounds()))
        {
            handle_collision(*it, steps);
            handle_end_collision();
        }
    }
    if (collided_object_types.size() == 0)
        handle_null_collision();
    collided_object_types.clear();
}

void set_position(const sf::Float2f &_position)
{
    position = _position;
    shape.setPosition(_position);
}

void Moveable::set_position(float x, float, y)
{
    position.x = x;
    position.y = y;
    shape.setPosition(x, y);
}