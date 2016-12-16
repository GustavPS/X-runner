#include "bird.h"

Bird::Bird(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::string &type,
           const sf::Texture *const texture,
           const float speed,
           const int direction,
           const float cooldown,
           const bool solid)
    : Movable_Object { position, size, type, solid, texture }
    , m_speed { speed }
    , m_direction { direction }
    , m_cooldown { cooldown }
{
    sf::Texture txt;
    txt.loadFromFile("Block_Ninja/idle.PNG");
    txt.setSmooth(false);
    m_shape.setTexture( new sf::Texture { txt } ); // memleak
}

int Bird::prepare_simulate(const float distance_modifier,
                           const float)
{
    // Set distance to direction
    m_distance.x = m_direction;

    if (m_player_debuff)
    {
        if (m_player_clock.getElapsedTime().asSeconds() < m_cooldown)
        {
            sf::Texture txt;
            txt.loadFromFile("Block_Ninja/idle_50.PNG");
            txt.setSmooth(false);
            m_shape.setTexture( new sf::Texture { txt } ); // memleak
        }
        else
        {
            sf::Texture txt;
            txt.loadFromFile("Block_Ninja/idle.PNG");
            txt.setSmooth(false);
            m_shape.setTexture( new sf::Texture { txt } ); // memleak
            m_player_debuff = false;
        }
    }

    // Apply speed
    m_distance *= m_speed;

    return Movable_Object::prepare_simulate(distance_modifier);
}

void Bird::handle_moving_collision(const Object *object,
                            const sf::Vector2f &steps)
{
    Movable_Object::handle_moving_collision(object, steps);

    const std::string type { object->get_type() };

    if (object->is_solid() || type == "bird_stopper")
    {
        if (steps.x != 0)
        {
            m_direction *= -1.f;
        }
    }
}

void Bird::handle_static_collision(const Object *object)
{
    Movable_Object::handle_static_collision(object);

    const std::string type { object->get_type() };

    if (type == "player")
    {
        if (!m_player_debuff)
        {
            m_player_clock.restart();
            m_player_debuff = true;
        }
    }
}