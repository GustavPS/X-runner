#include "nfbb.h"

NFBB::NFBB(const sf::Vector2f &position,
           const sf::Vector2f &size,
           const std::string &type,
           const sf::Texture *const texture)
    : Gravitating_Object { position, size, type, false, texture }
    // solid --------------------------------------^
{
}

std::vector<Object*> NFBB::simulate(const int total_simulations,
                                    const std::vector<const Object*>& objects)
{
    if (m_on_ground)
    {
        if (m_despawn_clock.getElapsedTime().asSeconds() >= 5.f)
        {
            m_delete_status = true;
        }
    }
    else
    {
        m_despawn_clock.restart();
    }

    return Gravitating_Object::simulate(total_simulations, objects);
}

void NFBB::handle_static_collision(const Object *object)
{
    Gravitating_Object::handle_static_collision(object);

    const std::string type { object->get_type() };

    if (type == "player")
    {
        m_delete_status = true;
    }
}

void NFBB::handle_end_collision()
{
    if (m_ground_collision)
    {
        m_on_ground = true;
    }

    Gravitating_Object::handle_end_collision();
}