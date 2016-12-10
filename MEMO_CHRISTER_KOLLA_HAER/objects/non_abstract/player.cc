#include "player.h"

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &dimensions,
               const std::vector<std::string> &types,
               float speed,
               float weight)
    : Gravitating_Object { position, dimensions, types, speed, weight }
{
    sf::Texture txt;
    txt.loadFromFile("player.png");
    shape.setTexture( new sf::Texture { txt } );
    // do some stuff, like texture of shape.
}

void Player::simulate(std::vector<Object*> &objects,
                      float distance_modifier,
                      float gravity_constant)
{
    sf::Vector2f distance;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        distance.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        distance.x = 1;
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     && on_ground && !on_quicksand)
        jumping = true;
    if (jumping)
        distance.y = -1.5;

    // Speed modifying debuffs
    float speed_modifier {1};

    if (on_quicksand)
        speed_modifier *= 0.75;

    if (slow_bird_count > 0)
    {
        if (slow_bird_clock.getElapsedTime().asSeconds() < 5)
        {
            speed_modifier *= 0.75 * slow_bird_count;
        }
        else
        {
            slow_bird_count = 0;
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
            boost_bird_count = 0;
        }
    }

    if (nfbb_count  > 0)
    {
        if (nfbb_clock.getElapsedTime().asSeconds() < 2)
        {
            speed_modifier = 0;
        }
        else
        {
            nfbb_count = 0;
        }
    }

    // Apply speed modifiers
    distance *= speed * speed_modifier;

    // Continue simulation
    Gravitating_Object::simulate(
        objects, distance_modifier, gravity_constant, distance);
}

#include <iostream>
bool Player::handle_collision(Object *object, const sf::Vector2f &steps)
{
    bool has_collided { Gravitating_Object::handle_collision(object, steps) };

    auto _types { object->get_types() };

    std::string _type { _types.at(0) };

    std::string _subtype;
    if (_types.size() > 1)
        _subtype = _types.at(1);

    /*Collision with types*/
    if (_type == "ground" && steps.y > 0)
    {
        jumping = false;
        on_ground = true;
        has_collided = true; //kan omittas pga Movable_Object::this_fun
    }
    else if (_type == "roof" && steps.y < 0)
    {
        jumping = false;
        has_collided = true; //kan omittas pga Movable_Object::this_fun
    }
    else if (_type == "slow_bird")
    {
        ++slow_bird_count;
        slow_bird_clock.restart();
        has_collided = true;  // används inte av detta objekt, kan omittas
    }
    else if (_type == "boost_bird")
    {
        ++boost_bird_count;
        boost_bird_clock.restart();
        has_collided = true; // ^^ (same for following)
    }
    else if (_type == "nfbb")
    {
        object->m_delete = true;
        ++nfbb_count;
        nfbb_clock.restart();
        has_collided = true;
    }

    /*Collision with subtypes*/
    if (_subtype == "quicksand" && steps.y > 0)
    {
        on_quicksand = true;
        has_collided = true;
    }

    return has_collided;
}

void Player::handle_end_collision()
{
    /*Collision has not occured with <x>*/
    if (collided_object_types.size() > 0)
    {
        if (on_ground
            && collided_object_types.find("ground")
                == collided_object_types.end())
        {
            on_ground = false;
        }
        if (on_quicksand
            && collided_object_types.find("quicksand")
                == collided_object_types.end())
        {
            on_quicksand = false;
        }
    }
    else
    {
        on_ground = false;
        on_quicksand = false;
    }
}
