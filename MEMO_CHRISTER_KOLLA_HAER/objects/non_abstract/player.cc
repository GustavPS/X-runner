#include "player.h"

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &dimensions,
               const std::vector<std::string> &types,
               float speed,
               float weight)
    : Gravitable { position, dimensions, types, speed, weight }
{
    // do some stuff, like texture of shape.
}

void Player::simulate(float distance_modifier,
              float gravity_modifier,
              const std::vector<Object*> &objects)
{
    // Gravitate me!
    gravitate(distance_modifier, gravity_modifier, objects);

    // Where do I move?
    sf::Vector2f distance;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        distance.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        distance.x = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        && on_ground && !on_quicksand)
    {
        //do jump stuff here
    }

    // Speed modifying debuffs
    float speed_modifier {1};

    if (on_quicksand)
        speed_modifier *= 0.75;

    if (slow_bird_count > 0)
    {
        if (slow_bird_clock.getElapsedTime().asSeconds() < 5)
        {
            speed_modifier *= 0.75 * speed_bird_count;
        }
        else
        {
            speed_bird_count = 0;
        }
    }

    if (boost_bird_count > 0)
    {
        if (boost_bird_clock.getElapsedTime().asSeconds() < 5)
        {
            speed_modifier *= 1.25 * boost_bird_count;
        }
        else
        {
            boord_bird_count = 0;
        }
    }

    if (nfbb_clock.getElapsedTime().asSeconds() < 2)
        speed_modifier = 0;
    

    // Execute move
    distance.x *= speed * speed_modifier * distance_modifier;
    distance.y *= speed * speed_modifier * distance_modifier;
    //distance *= speed * speed_modifier * distance_modifier;
    move(distance, objects);
}

void Player::handle_collision(Object &object, const sf::Vector2f &steps)
{
    auto _types { object->get_types() };

    std::string _type { _types.at(0) };

    std::string _subtype;
    if (_types.size() > 1)
        _subtype = _types.at(1); 

    /*Collision with types*/
    if (_type == "ground" && steps.y > 0
     && collided_object_types.find(_type) == collided_object_types.end())
    {
        on_ground = true;
        set_position(position.x, position.y - steps.y);
        collided_object_types.insert(_type);
    }
    else if (_type == "roof" && steps.y < 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x, position.y - steps.y);
        collided_object_types.insert(_type);
    }
    else if (_type == "wall" && steps.x != 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x - steps.x, position.y);
        collided_object_types.insert(_type);
    }
    else if (_type == "slow_bird")
    {
        ++slow_bird_count;
        slow_bird_clock.restart();
        collided_object_types.insert(_type);
    }
    else if (_type == "boost_bird")
    {
        ++boost_bird_count;
        boost_bird_clock.restart();
        collided_object_types.insert(_type);
    }
    else if (_type == "nfbb")
    {
        delete object;
        object = nullptr;
        nfbb_clock.restart();
        collided_object_types.insert(_type);
    }

    /*Collision with subtypes*/
    if (_subtype == "quicksand" && steps.y > 0)
    {
        on_quicksand = true;
        collided_object_types.insert(_subtype);
    }
}

void Player::handle_end_collision()
{
    /*Collision has not occured with <x>*/
    if (collided_object_types.find("ground") == collided_object_types.end())
    {
        on_ground = false;
    }
    if (collided_object_types.find("quicksand") == collided_object_types.end())
    {
        on_quicksand = false;
    }
}

void Player::handle_null_collision()
{
    on_ground = false;
    on_quicksand = false;
}
