#include "nfbb.h"

NFBB::NFBB(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::string &type)
    : Gravitating_Object { position, size, type }
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
        if (despawn_clock.getElapsedTime().asSeconds() >= 5)
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

void NFBB::handle_collision(const Object *object, 
                            const sf::Vector2f &steps)
{
    Gravitating_Object::handle_collision(object, steps);

    if (object->is_solid())
    {
        if (steps.y > 0.f)
        {
            on_ground = true;
        }
    }

    const std::string type { object->get_type() };

    if (type == "player")
    {
        m_delete_status = true;
    }
}