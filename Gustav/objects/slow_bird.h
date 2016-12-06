#ifndef SLOW_BIRD_H
#define SLOW_BIRD_H
#include "NPC.h"
#include "net.h"
#include <vector>
#include <unordered_set>

class Slow_Bird : public NPC
{
private:
    sf::Clock clock;
    bool collided(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders);
    int direction {1};
    std::vector<Net*> nets;

public:
    Slow_Bird(const sf::Vector2f&, const sf::Vector2f&, const std::string&);
    void try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders) override;
    void iamnull() {};
public:
    void simulate();
    std::vector<Net*> get_nets() {return nets;};
};

#endif
