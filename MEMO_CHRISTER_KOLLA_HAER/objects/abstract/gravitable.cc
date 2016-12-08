#include "gravitable.h"

Gravitable::Gravitable(const sf::Vector2f &position,
                       const sf::Vector2f &dimensions,
                       const std::vector<std::string> &types,
                       float speed
                       float weight)
    : Movable { position, dimensions, types, speed }
    , weight { weight }
{}

Gravitable::gravitate(float distance_modifier,
                      float gravity_modifier,
                      const std::vector<Object*>& objects)
{
    //do gravvy stuff
    //call move()
}