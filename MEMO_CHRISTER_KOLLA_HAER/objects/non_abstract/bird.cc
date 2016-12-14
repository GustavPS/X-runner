#include "bird.h"

Bird::Bird(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::string &type,
           const float speed)
    : Movable_Object { position, size, type }
    , speed { speed }
    , m_direction { 1.f }
{
    sf::Texture txt;
    txt.loadFromFile("Block_Ninja/idle.PNG");
    shape.setTexture( new sf::Texture { txt } ); // memleak
}

int Bird::prepare_simulate(const float distance_modifier,
                           const float)
{
    distance.x = m_direction;

    if (player_debuff)
    {
        if (player_clock.getElapsedTime().asSeconds() < 2.f)
        {
            sf::Texture txt;
            txt.loadFromFile("Block_Ninja/idle_50.PNG");
            txt.setSmooth(false);
            shape.setTexture( new sf::Texture { txt } ); // memleak
        }
        else
        {
            sf::Texture txt;
            txt.loadFromFile("Block_Ninja/idle.PNG");
            txt.setSmooth(false);
            shape.setTexture( new sf::Texture { txt } ); // memleak
            player_debuff = false;
        }
    }

    // Apply speed
    distance *= speed;

    return Movable_Object::prepare_simulate(distance_modifier);
}

void Bird::handle_collision(const Object *object,
                            const sf::Vector2f &steps)
{
    Movable_Object::handle_collision(object, steps);

    if (object->is_solid())
    {
        if (steps.x != 0)
        {
            m_direction *= -1.f;
        }
    }

    const std::string type { object->get_type() };

    if (type == "player")
    {
        if (!player_debuff)
        {
            player_clock.restart();
            player_debuff = true;
        }
    }
}