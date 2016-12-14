#include "boost_bird.h"

//#include "../abstract/gravitable.h"
#include "nfbb.h"

Boost_Bird::Boost_Bird(const sf::Vector2f &position,
                       const sf::Vector2f &size,
                       const std::string &type,
                       const float speed)
    : Bird { position, size, type, speed }
{
    sf::Texture txt;
    txt.loadFromFile("Block_Ninja/idle.PNG");
    shape.setTexture( new sf::Texture { txt } ); // memleak
}

#include <iostream>
std::vector<Object*> Boost_Bird::simulate(const int total_simulations,
                                          const std::vector<const Object*> &objects)
{
    auto new_objects { Bird::simulate(total_simulations, objects) };

    if (nfbb_clock.getElapsedTime().asSeconds() >= 6.f)
    {
        new_objects.push_back( new NFBB
                               {
                                   shape.getPosition(),
                                   sf::Vector2f { 16.f, 16.f },
                                   "nfbb"
                               } );

        std::cerr << new_objects.size() << " ";

        nfbb_clock.restart();
    }

    return new_objects;
}