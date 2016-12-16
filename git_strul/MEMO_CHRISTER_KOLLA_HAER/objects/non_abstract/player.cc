#include "player.h"

#include <cmath>

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &size,
               const std::string &type,
               const sf::Texture *const texture,
               const float speed)
    : Gravitating_Object { position, size, type, false, texture }
    // solid --------------------------------------^
    , m_speed { speed }
{}

int Player::prepare_simulate(const float distance_modifier,
                             const float gravity_constant)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_distance.x = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_distance.x = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     && m_on_ground && !m_quicksand_debuff)
        m_jumping = true;
    if (m_jumping)
        m_distance.y = -1.5f;
        // --------------^
        // has to jump more than -1.f to make up for gravity

    // Speed modifying debuffs
    float speed_modifier {1.f};

    if (m_quicksand_debuff)
        speed_modifier *= 0.33f;

    if (m_slow_bird_debuffs.size())
    {
        if (m_slow_bird_clock.getElapsedTime().asSeconds() < 2.f)
        {
            speed_modifier *= std::pow(0.66f, m_slow_bird_debuffs.size());
        }
        else
        {
            m_slow_bird_debuffs.clear();
        }
    }

    if (m_boost_bird_buffs.size())
    {
        if (m_boost_bird_clock.getElapsedTime().asSeconds() < 2.f)
        {
            speed_modifier *= std::pow(1.1f, m_boost_bird_buffs.size());
        }
        else
        {
            m_boost_bird_buffs.clear();
        }
    }

    if (m_nfbb_debuff)
    {
        if (m_nfbb_clock.getElapsedTime().asSeconds() < 2.f)
        {
            speed_modifier *= 0.66f;
            //boost_bird_buffs.clear();
        }
        else
        {
            m_nfbb_debuff = false;
        }
    }

    // Apply speed and speed_modifier
    m_distance *= m_speed * speed_modifier;

    // Continue simulation
    // Return the number of simulations needed for this object
    return Gravitating_Object::prepare_simulate(
        distance_modifier, gravity_constant);
}

void Player::handle_moving_collision(const Object *object, 
                              const sf::Vector2f &steps)
{
    Gravitating_Object::handle_moving_collision(object, steps);

    const std::string type { object->get_type() };

    if (object->is_solid())
    {
        if (steps.y > 0.f)
        {
            if (type == "quicksand")
            {
                m_quicksand_collision = true;
            }
        }
    }
}

void Player::handle_static_collision(const Object *object)
{
    Gravitating_Object::handle_static_collision(object);

    const std::string type { object->get_type() };

    if (type == "slow_bird" || type == "bomb_bird")
    {
        if (m_slow_bird_debuffs.find(object)
            == m_slow_bird_debuffs.end())
        {
            m_slow_bird_clock.restart();
            m_slow_bird_debuffs.insert(object);
        }
    }
    else if (type == "boost_bird")
    {
        if (m_boost_bird_buffs.find(object)
            == m_boost_bird_buffs.end())
        {
            m_boost_bird_clock.restart();
            m_boost_bird_buffs.insert(object);
        }
    }
    else if (type == "nfbb" && !m_roof_collision && !m_wall_collision)
    {
        m_nfbb_clock.restart();
        m_nfbb_debuff = true;
    }
}

void Player::handle_end_collision()
{
    if (m_ground_collision)
    {
        m_jumping = false;
        m_on_ground = true;
    }
    else
    {
        m_on_ground  = false;
    }
    
    if (m_roof_collision)
    {
        m_jumping = false;
    }

    if (m_quicksand_collision)
    {
        m_quicksand_debuff = true;
    }
    if (!m_quicksand_collision)
    {
        m_quicksand_debuff = false;
    }

    Gravitating_Object::handle_end_collision();
}

void Player::collision_state_cleanup()
{
    m_quicksand_collision = false;
    Gravitating_Object::collision_state_cleanup();
}
