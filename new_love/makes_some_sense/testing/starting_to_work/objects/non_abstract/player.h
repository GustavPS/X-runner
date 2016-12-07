#ifndef PLAYER_H
#define PLAYER_H

#include "../abstract/gravitable.h"

class Player : public Gravitable
{
    public:
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&,
               float);

        void simulate(float,
                      float,
                      const std::vector<Object*>&) override;

    private:
        void handle_collision(const std::string &type) override;
};

#endif