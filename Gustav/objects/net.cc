#include "net.h"

Net::Net(const sf::Vector2f& p, const sf::Vector2f& dimensions, const std::string& str)
    : NPC{p, dimensions, str}
{

}

bool Net::simulate()
{
    if(clock.getElapsedTime().asSeconds() >= 5)
    {
        return true;
    }
    return false;
}

void Net::try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders)
{
    position.y += to.y;
    shape.setPosition(position);



    bool side {false};

    for (const auto object : objects)
    {
        if (shape.getGlobalBounds().intersects(
                    object->shape.getGlobalBounds()))
        {
            if (object->name == "top")
            {
                if (!side)
                    position.y -= to.y;
                colliders.insert(object->name);
                side = true;
            }
            shape.setPosition(position);
        }
    }
}
