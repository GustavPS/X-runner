#ifndef NET_H
#define NET_H
#include "NPC.h"

class Net : public NPC
{
private:
    sf::Clock clock;

public:
    Net(const sf::Vector2f&, const sf::Vector2f&, const std::string&);
    void try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders);
    void iamnull() {};
    bool simulate();

};

#endif
