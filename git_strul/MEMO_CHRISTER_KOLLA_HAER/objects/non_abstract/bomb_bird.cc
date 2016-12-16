#include "bomb_bird.h"

#include "nfbb.h"

Bomb_Bird::Bomb_Bird(const sf::Vector2f &position,
                       const sf::Vector2f &size,
                       const std::string &type,
                       const sf::Texture *const texture,
                       const float speed,
                       const int direction,
                       const sf::Texture *const nfbb_texture)
    : Slow_Bird { position, size, type, texture, speed, direction }
    , m_nfbb_texture { nfbb_texture }
{
    sf::Texture txt;
    txt.loadFromFile("Block_Ninja/idle.PNG");
    m_shape.setTexture( new sf::Texture { txt } ); // memleak
}

std::vector<Object*> Bomb_Bird::simulate(const int total_simulations,
                                          const std::vector<const Object*> &objects)
{
    auto new_objects { Slow_Bird::simulate(total_simulations, objects) };

    // Drop a NFBB every 10 seconds
    if (m_nfbb_clock.getElapsedTime().asSeconds() >= 10.f)
    {
        // Wait until position.x % block_width == (block_width - nfbb_width) / 2 
        // so that the NFBB spawns centered on a block
        if (static_cast<int>(m_shape.getPosition().x) % 32 == 4)
        {
            new_objects.push_back( new NFBB
                               {
                                   m_shape.getPosition(), // position
                                   sf::Vector2f { 24.f, 24.f }, // size
                                   "nfbb", // type
                                   m_nfbb_texture // texture
                               } );

            m_nfbb_clock.restart();
        }
    }

    return new_objects;
}