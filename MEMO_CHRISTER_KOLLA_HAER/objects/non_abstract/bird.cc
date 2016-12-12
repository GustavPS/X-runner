#include "bird.h"

Bird::Bird(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::vector<std::string> &types,
           float speed)
    : Movable_Object { position, size, types, speed }
    , m_direction { 1 }
{
    m_interactable_status = true;
    sf::Texture txt;
    txt.loadFromFile("player.png");
    shape.setTexture( new sf::Texture { txt } ); // memleak
}

int Bird::prepare_simulate(std::vector<Object*> &objects,
                           const float distance_modifier,
                           const float)
{
    check_collision(objects);

    distance.x = m_direction;

    if (player_debuff)
    {
        if (player_clock.getElapsedTime().asSeconds() < 2)
        {
            sf::Texture txt;
            txt.loadFromFile("player_50.png");
            shape.setTexture( new sf::Texture { txt } ); // memleak
        }
        else
        {
            sf::Texture txt;
            txt.loadFromFile("player.png");
            shape.setTexture( new sf::Texture { txt } ); // memleak
            player_debuff = false;
        }
    }

    distance *= speed;

    return Movable_Object::prepare_simulate(distance_modifier);
}
#include <iostream>
void Bird::simulate(const int total_simulations,
                    std::vector<Object*> &objects)
{
    check_collision(objects);
    
    Movable_Object::simulate(
        total_simulations, objects);
}

bool Bird::handle_collision(Object *object, const sf::Vector2f &steps)
{
    bool has_collided { Movable_Object::handle_collision(object, steps) };

    const std::string _type { object->get_types().at(0) };

    if (_type == "wall")
    {
        m_direction *= -1;
        has_collided = true;
    }
    else if (_type == "player")
    {
        if (!player_debuff)
        {
            player_clock.restart();
            player_debuff = true;
        }
    }
    return has_collided;
}