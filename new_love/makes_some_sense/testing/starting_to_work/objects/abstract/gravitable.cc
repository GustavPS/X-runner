#include "gravitable.h"

Gravitable::Gravitable(const sf::Vector2f &position,
                       const sf::Vector2f &dimensions,
                       const std::string &type,
                       float speed)
    : Movable { position, dimensions, type, speed }
{}

Gravitable::gravitate(float distance_modifier,
                      float gravity_modifier,
                      const std::vector<Object*>& objects)
{
    //do gravvy stuff
    //call move()
}