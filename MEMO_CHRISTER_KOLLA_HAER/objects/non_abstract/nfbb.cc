#include "nfbb.h"

NFBB::NFBB(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::vector<std::string> &types)
    : Gravitating_Object { position, size, types }
{
    sf::Texture txt;
    txt.loadFromFile("player.png");
    shape.setTexture( new sf::Texture { txt } ); // memleak
    // do some stuff, like texture of shape.
}

std::vector<Object*> NFBB::simulate(const int total_simulations,
                                    const std::vector<const Object*>& objects)
{
    if (on_ground)
    {
        if (despawn_clock.getElapsedTime().asSeconds() >= 3)
        {
            m_delete_status = true;
        }
    }
    else
    {
        despawn_clock.restart();
    }

    return Gravitating_Object::simulate(total_simulations, objects);
}

bool NFBB::handle_collision(const Object *object, 
                            const sf::Vector2f &steps)
{
    bool has_collided { Gravitating_Object::handle_collision(object, steps) };

    const std::string _type { object->get_types().at(0) };

    if (_type == "ground" && steps.y > 0)
    {
        on_ground = true;
        has_collided = true;
    }
    else if (_type == "player")
    {
        m_delete_status = true;
    }

    return has_collided;
}