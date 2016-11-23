//
// Created by gustav on 2016-11-16.
//

#ifndef SFML_COLLISION_H
#define SFML_COLLISION_H
#include "Platform.h"
#include "Player.h"

class Collision {
public:
    Collision() = default;
    bool check_collision(Player player, Platform platform) const;
    bool check_collision(Player player, Player player1) const {return false;};
};


#endif //SFML_COLLISION_H
