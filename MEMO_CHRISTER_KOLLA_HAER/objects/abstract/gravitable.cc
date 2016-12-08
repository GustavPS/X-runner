#include "gravitable.h"

Gravitable::Gravitable(const sf::Vector2f &position,
                       const sf::Vector2f &dimensions,
                       const std::vector<std::string> &types,
                       float speed,
                       float weight)
    : Movable { position, dimensions, types, speed }
    , weight { weight }
{}
#include <iostream>
void Gravitable::simulate(float distance_modifier,
                      float gravity_modifier,
                      std::vector<Object*>& objects)
{
    sf::Vector2f distance;
    count = 1;
    distance.y = gravity_modifier * count * distance_modifier;
    move(distance, objects);
}