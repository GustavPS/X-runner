#include <cmath>

#include "player.h"

Player::Player(const sf::Vector2f &position, const sf::Vector2f &dimensions, int gid, const std::string &name)
    : Object { position, dimensions, name }
    , gid { gid }
{
    texture.loadFromFile("player.png");
    sprite.setTexture(texture);
    sprite.setPosition(position);
    //sprite.setScale(0.9, 0.9);
}

/*Player::Player(const Player *rhs)
    : Player { rhs->position, rhs->dimensions, rhs->gid, rhs->name }
{
    delete rhs;
}*/

sf::Sprite Player::get_sprite() const
{
    return sprite;
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}
#include <iostream>
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
            if (object->name == "top" || object->name == "bottom")
            {
                if (object->name == "top" &&
                    to.y > 0)
                    {
                        if (!top)
                            position.y -= to.y;
                        colliders.insert(object->name);
                        top = true;
                        can_jump = true;
                    }
                if (object->name == "bottom" &&
                    to.y < 0)
                    {
                        if (!top)
                            position.y -= to.y;
                        colliders.insert(object->name);
                        top = true;
                    }
                
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
            colliders.insert(object->name);
            if (object->name == "side" && to.x != 0)
            {
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