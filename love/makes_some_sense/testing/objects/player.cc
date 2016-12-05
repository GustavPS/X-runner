#include <cmath>

#include "player.h"

Player::Player(const std::string &name, const sf::Vector2f &position, const sf::Vector2f &dimensions, int gid)
    : Object { name, position, dimensions }
    , gid { gid }
{
    texture.loadFromFile("player.png");
    shape.setTexture(texture);
}

bool Player::try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders)
{

    
    //std::cerr << to.x << " " << to.y << "\n";
    position.y += to.y;
    //position.y += to.y;
    sprite.setPosition(position);

    bool top = false;
    //bool side = false;

    for (const auto object : objects)
    {
        if (sprite.getGlobalBounds().intersects(
                object->shape.getGlobalBounds()))
        {
            //if (object->name == "jump") std::cerr << "jump";
            if (object->name == "top" || object->name == "bottom" || object->name == "jump")
            {
                //std::cerr << object->name;
                if (object->name == "top" &&
                    to.y > 0)
                    {
                        //std::cerr << "top";
                        if (!top)
                            position.y -= to.y;
                        colliders.insert(object->name);
                        top = true;
                        //can_jump = true;
                    }
                if (object->name == "bottom" &&
                    to.y < 0)
                    {
                        //std::cerr << "bottom";
                        if (!top)
                            position.y -= to.y;
                        colliders.insert(object->name);
                        top = true;
                    }
                if (object->name == "jump" && to.y > 0)
                    can_jump = true;
                
            }
            sprite.setPosition(position);
            //return true;
        }

    }
    position.x += to.x;
    sprite.setPosition(position);

    //bool top = false;
    bool side = false;
    for (const auto object : objects)
    {
        if (sprite.getGlobalBounds().intersects(
                object->shape.getGlobalBounds()))
        {
            if (object->name == "side" && to.x != 0)
            {
                //std::cerr << "side";
                if (!side)
                    position.x -= to.x;
                colliders.insert(object->name);
                side = true;   
            }
            sprite.setPosition(position);
            //return true;
        }
    }
    return false;
}