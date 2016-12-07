#include "player.h"

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &dimensions,
               const std::string &type,
               float speed)
    : Gravitable { position, dimensions, type, speed }
{

}

void Player::simulate(float distance_modifier,
              float gravity_modifier,
              const std::vector<Object*> &objects)
{
    gravitate(distance_modifier, gravity_modifier, objects);

    sf::Vector2f distance;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        distance.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        distance.x = 1;
    // jumping goes here

    distance.x *= speed * distance_modifier;
    distance.y *= speed * distance_modifier;
    move(distance, objects);
}

void handle_collision(Object &object, const sf::Vector2f &steps)
{
    if (object->get_type() == "ground" && steps.y > 0)
    {
        set_position(position.x, position.y - steps.y);
        can_jump = true;
    }
    else if (object->get_type() == "roof" && steps.y < 0)
    {
        set_position(position.x, position.y - steps.y);
    }
    else if (object->get_type() == "wall" && steps.x != 0)
    {
        set_position(position.x - steps.x, position.y);
    }
    else if (object->get_type() == "slow_bird")
    {
        speed *= 0.75;
        //decrease player speed for 5s
    }
    else if (object->get_type() == "boost_bird")
    {
        speed *= 1.25;
        //increase player speed for 5s
    }
    else if (object->get_type() == "nfbb")
    {
        speed = 0;
        delete object;
        object = nullptr;
        //stun player for 2s
    }
    else if (object->get_type() == "quicksand" && steps.y > 0)
    {
        set_position(position.x, position.y - steps.y);
        can_jump = false;
    }
}

