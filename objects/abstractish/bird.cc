#include "bird.h"

Bird::Bird(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::string &type,
           const sf::Texture *texture,
           const float speed,
           const int direction,
           const float cooldown,
           const bool solid)
    : Movable_Object { position, size, type, solid, texture }
    , m_speed { speed }
    , m_direction { direction }
    , m_cooldown { cooldown }
{}

int Bird::prepare_simulate(const float distance_modifier,
                           const float)
{
    // Set distance to direction
    m_distance.x = m_direction;

    // Set opacity to after collision with player during the duration <m_cooldown>
    if (m_player_debuff)
    {
        if (m_player_clock.getElapsedTime().asSeconds() < m_cooldown)
        {
            m_shape.setFillColor(sf::Color(255, 255, 255, 128));
        }
        else
        {
            m_player_debuff = false;
            m_shape.setFillColor(sf::Color(255, 255, 255, 255));
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