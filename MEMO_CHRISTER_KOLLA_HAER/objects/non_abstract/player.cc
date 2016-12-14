#include "player.h"
#include "bird.h"

#include <cmath>

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &size,
               const std::string &type,
               const float speed)
    : Gravitating_Object { position, size, type }
    , speed { speed }
{
    sf::Texture txt;
    txt.loadFromFile("Block_Ninja/idle.PNG");
    shape.setTexture( new sf::Texture { txt } ); // memleak
    // do some stuff, like texture of shape.
}

int Player::prepare_simulate(const float distance_modifier,
                             const float gravity_constant)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        distance.x = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        distance.x = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     && on_ground && !quicksand_debuff)
        jumping = true;
    if (jumping)
        distance.y = -1.5f;

    // Speed modifying debuffs
    float speed_modifier {1.f};

    if (quicksand_debuff)
        speed_modifier *= 0.33f;

    if (slow_bird_debuffs.size())
    {
        if (slow_bird_clock.getElapsedTime().asSeconds() < 2.f)
        {
            speed_modifier *= std::pow(0.66f, slow_bird_debuffs.size());
        }
        else
        {
            slow_bird_debuffs.clear();
        }
    }

    if (boost_bird_buffs.size())
    {
        if (boost_bird_clock.getElapsedTime().asSeconds() < 5.f)
        {
            speed_modifier *= std::pow(1.166f, boost_bird_buffs.size());
        }
        else
        {
            boost_bird_buffs.clear();
        }
    }

    if (nfbb_debuff)
    {
        if (nfbb_clock.getElapsedTime().asSeconds() < 2.f)
        {
            speed_modifier *= 0.66f;
            //boost_bird_buffs.clear();
        }
        else
        {
            nfbb_debuff = false;
        }
    }

    // Apply speed and speed_modifier
    distance *= speed * speed_modifier;

    // Continue simulation
    // Return the number of simulations needed for this object
    return Gravitating_Object::prepare_simulate(
        distance_modifier, gravity_constant);
}

void Player::handle_collision(const Object *object, 
                              const sf::Vector2f &steps)
{
    Gravitating_Object::handle_collision(object, steps);

    if (object->is_solid())
    {
        if (steps.y > 0.f)
        {
            jumping = false;
            on_ground = true;
        }
        else if (steps.y < 0.f)
        {
            jumping = false;
        }
    }

    const std::string type { object->get_type() };

    if (type == "slow_bird")
    {
        if (slow_bird_debuffs.find(object)
            == slow_bird_debuffs.end())
        {
            slow_bird_clock.restart();
            slow_bird_debuffs.insert(object);
        }
    }
    else if (type == "boost_bird")
    {
        if (boost_bird_buffs.find(object)
            == boost_bird_buffs.end())
        {
            boost_bird_clock.restart();
            boost_bird_buffs.insert(object);
        }
    }
    else if (type == "nfbb")
    {
        nfbb_clock.restart();
        nfbb_debuff = true;
    }
    else if (type == "quicksand")
    {
        if (steps.y > 0.f)
        {
            quicksand_debuff = true;
            m_quicksand_collision = true;
        }
    }
}

void Player::handle_end_collision(const sf::Vector2f &steps)
{
    /*Collision has not occured with <x>*/
    if (steps.y != 0.f)
    {
        if (!m_ground_collision)
        {
            on_ground = false;
        }

        if (!m_quicksand_collision)
        {
            quicksand_debuff = false;
        }
    }

    Gravitating_Object::handle_end_collision(steps);
}

void Player::collision_state_cleanup()
{
    m_quicksand_collision = false;
    Gravitating_Object::collision_state_cleanup();
}
