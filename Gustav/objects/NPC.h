#ifndef NPC_H
#define NPC_H

#include "object.h"
#include <vector>
#include <unordered_set>

class NPC : public Object
{
private:
    int speed {50};

public:
NPC(const sf::Vector2f&, const sf::Vector2f&, const std::string&);
    virtual void try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders) = 0;
    int get_speed() { return speed; };
};

#endif
