#include "boost_bird.h"

//#include "../abstract/gravitable.h"
#include "nfbb.h"

Boost_Bird::Boost_Bird(const sf::Vector2f &position,
                       const sf::Vector2f &size,
                       const std::vector<std::string> &types,
                       float speed)
    : Bird { position, size, types, speed }
{
    sf::Texture txt;
    txt.loadFromFile("player.png");
    shape.setTexture( new sf::Texture { txt } ); // memleak
}

#include <iostream>
std::vector<Object*> Boost_Bird::simulate(const int total_simulations,
                                          const std::vector<const Object*> &objects)
{
    auto new_objects { Bird::simulate(total_simulations, objects) };

    if (nfbb_clock.getElapsedTime().asSeconds() >= 12)
    {
        new_objects.push_back( new NFBB
                               {
                                   shape.getPosition(),
                                   sf::Vector2f { 24, 12 },
                                   std::vector<std::string> { "nfbb" }
                               } );

        std::cerr << new_objects.size() << " ";

        nfbb_clock.restart();
    }

    return new_objects;
}