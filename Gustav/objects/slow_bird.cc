#include "slow_bird.h"
#include "net.h"
#include <iostream>

Slow_Bird::Slow_Bird(const sf::Vector2f& p, const sf::Vector2f& dimensions, const std::string& str)
    : NPC{p, dimensions, str}
{

}

void Slow_Bird::simulate()
{
    if(clock.getElapsedTime().asSeconds() >= 5)
    {
        nets.push_back(new Net{position, sf::Vector2f{5, 5}, "Net"});
        clock.restart();
    }
    for(int i {0}; i < nets.size(); ++i)
    {
        if(nets.at(i)->simulate())
        {
            delete nets.at(i);
            nets.erase(nets.begin() + i);
        }
    }
}

bool Slow_Bird::collided(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders)
{
    return false;
}

void Slow_Bird::try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders)
{
    position.x += (direction * to.x);
    shape.setPosition(position);



    bool side {false};

    for (const auto object : objects)
    {
        if (shape.getGlobalBounds().intersects(
                    object->shape.getGlobalBounds()))
        {
            if (object->name == "side")
            {
                if (!side)
                    position.x -= (direction * to.x);
                colliders.insert(object->name);
                side = true;
                direction = direction * -1;
            }
            shape.setPosition(position);
        }
    }

    /*
    

    //std::cerr << to.x << " " << to.y << "\n";
    position.y += to.y;
    //position.y += to.y;
    shape.setPosition(position);

    bool top = false;
    //bool side = false;
    for (const auto object : objects)
    {
        if (shape.getGlobalBounds().intersects(
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
            shape.setPosition(position);
            //return true;
        }

    }
    position.x += to.x;
    shape.setPosition(position);

    //bool top = false;
    bool side = false;
    for (const auto object : objects)
    {
        if (shape.getGlobalBounds().intersects(
                object->shape.getGlobalBounds()))
        {
            if (object->name == "side" && to.x != 0)
            {
                if (!side)
                    position.x -= to.x;
                colliders.insert(object->name);
                side = true;   
            }
            shape.setPosition(position);
            //return true;
        }
    }
    return false;
    */
}
