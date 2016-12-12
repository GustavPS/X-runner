#include "player.h"
#include "bird.h"

#include <cmath>

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &size,
               const std::vector<std::string> &types,
               float speed,
               float weight)
    : Gravitating_Object { position, size, types, speed, weight }
{
    sf::Texture txt;
    txt.loadFromFile("player.png");
    shape.setTexture( new sf::Texture { txt } ); // memleak
    // do some stuff, like texture of shape.
}

int Player::prepare_simulate(std::vector<Object*> &objects,
                             const float distance_modifier,
                             const float gravity_constant)
{
    check_collision(objects);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        distance.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        distance.x = 1;
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     && on_ground && !quicksand_debuff)
        jumping = true;
    if (jumping)
        distance.y = -1.5;

    // Speed modifying debuffs
    float speed_modifier {1};

    if (quicksand_debuff)
        speed_modifier *= 0.75;

    if (slow_bird_debuffs.size())
    {
        if (slow_bird_clock.getElapsedTime().asSeconds() < 2)
        {
            speed_modifier *= std::pow(0.66, slow_bird_debuffs.size());
        }
        else
        {
            slow_bird_debuffs.clear();
        }
    }

    if (boost_bird_buffs.size())
    {
        if (boost_bird_clock.getElapsedTime().asSeconds() < 2)
        {
            speed_modifier *= std::pow(1.33, boost_bird_buffs.size());
        }
        else
        {
            boost_bird_buffs.clear();
        }
    }

    if (nfbb_debuff)
    {
        if (nfbb_clock.getElapsedTime().asSeconds() < 1)
        {
            speed_modifier = 0;
        }
        else
        {
            nfbb_debuff = false;
        }
    }

    // Apply speed modifiers
    distance *= speed * speed_modifier;

    // Continue simulation
    // Return the number of simulations needed for this object
    return Gravitating_Object::prepare_simulate(
        distance_modifier, gravity_constant);
}

void Player::simulate(const int total_simulations,
                      std::vector<Object*> &objects)
{
    // Check collision
    check_collision(objects);

    // Continue simulation
    Gravitating_Object::simulate(
        total_simulations, objects);
}

bool Player::handle_collision(Object *object, const sf::Vector2f &steps)
{
    bool has_collided { Gravitating_Object::handle_collision(object, steps) };

    const auto _types { object->get_types() };

    const std::string &_type { _types.at(0) };

    const std::string _subtype { _types.size() > 1
                                 ? _types.at(1)
                                 : std::string() };

    /*Collision with types*/
    if (_type == "ground" && steps.y > 0)
    {
        jumping = false;
        on_ground = true;
        has_collided = true;
    }
    else if (_type == "roof" && steps.y < 0)
    {
        jumping = false;
        has_collided = true;
    }
    else if (_type == "slow_bird")
    {
        if (slow_bird_debuffs.find(object)
            == slow_bird_debuffs.end())
        {
            slow_bird_clock.restart();
            slow_bird_debuffs.insert(object);
            has_collided = true;
        }
    }
    else if (_type == "boost_bird")
    {
        if (true)
        {
            boost_bird_clock.restart();
            boost_bird_buffs.insert(object);
            has_collided = true;
        }
    }
    else if (_type == "nfbb")
    {
        nfbb_clock.restart();
        nfbb_debuff = true;
        has_collided = true;
    }

    /*Collision with subtypes*/
    if (_subtype == "quicksand" && steps.y > 0)
    {
        quicksand_debuff = true;
        has_collided = true;
    }

    return has_collided;
}

void Player::handle_end_collision(const sf::Vector2f &steps)
{
    /*Collision has not occured with <x>*/
    if (steps.y)
    {
        if (collided_object_types.size() > 0)
        {
            if (on_ground)
            {
                if (collided_object_types.find("ground")
                    == collided_object_types.end())
                {
                    on_ground = false;
                }
            }
            if (quicksand_debuff)
            {
                if (collided_object_types.find("quicksand")
                    == collided_object_types.end())
                {
                    quicksand_debuff = false;
                }
            }
        }
        else
        {
            on_ground = false;
            quicksand_debuff = false;
        }
    }
}
