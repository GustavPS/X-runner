#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

#include <vector>
#include <unordered_set>

class Player : public Object
{
    public:
        Player(const sf::Vector2f&, const sf::Vector2f&, int, const std::string&);
        //Player(const Player *rhs);
        sf::Sprite get_sprite() const;
        void draw(sf::RenderWindow &window) const;
        bool try_move(const sf::Vector2f &to, const std::vector<Object*> &objects, std::unordered_set<std::string> &colliders);
        void iamnull() {}
        bool can_jump = false;
    
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int gid;
};

#endif