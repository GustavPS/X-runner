//
// Created by gustav on 2016-11-16.
//

#ifndef SFML_PLATFORM_H
#define SFML_PLATFORM_H
#include <vector>
#include "Block.h"
#include "SFML/Graphics.hpp"

class Platform {
private:
    std::vector<Block> blocks;
    int x;
    int y;

public:
    Platform(int x, int y);
    void add_block(Block block);
    void draw_horizontal(sf::RenderWindow & window);
    void draw_vertical();
    std::vector<Block> get_blocks() const {return blocks;};
};


#endif //SFML_PLATFORM_H
