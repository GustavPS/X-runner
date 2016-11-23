//
// Created by gustav on 2016-11-16.
//

#include "Collision.h"


bool Collision::check_collision(Player player, Platform platform) const
{
    std::vector<Block> blocks = platform.get_blocks();
    for(std::size_t i {}; i < blocks.size(); ++i)
    {
        if(player.getShape().getGlobalBounds().intersects(blocks.at(i).get_shape().getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}