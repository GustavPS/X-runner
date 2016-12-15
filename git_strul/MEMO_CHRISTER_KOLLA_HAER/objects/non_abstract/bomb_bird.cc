#include "bomb_bird.h"

//#include "../abstract/gravitable.h"
#include "nfbb.h"

Bomb_Bird::Bomb_Bird(const sf::Vector2f &position,
                       const sf::Vector2f &size,
                       const std::string &type,
                       const float speed)
    : Bird { position, size, type, speed }
{
    sf::Texture txt;
    txt.loadFromFile("Block_Ninja/idle.PNG");
    shape.setTexture( new sf::Texture { txt } ); // memleak
}


std::vector<Object*> Bomb_Bird::simulate(const int total_simulations,
                                          const std::vector<const Object*> &objects)
{
    auto new_objects { Bird::simulate(total_simulations, objects) };

    if (nfbb_clock.getElapsedTime().asSeconds() >= 10.f)
    {
        // wait until position.x % block_width == (block_width - nfbb_width) / 2 
        // so that the NFBB spawns centered on a block
        if (static_cast<int>(shape.getPosition().x) % 32 == 4)
        {
            new_objects.push_back( new NFBB
                               {
                                   shape.getPosition(),
                                   sf::Vector2f { 24.f, 24.f },
                                   "nfbb"
                               } );

            nfbb_clock.restart();
        }
    }

    return new_objects;
}