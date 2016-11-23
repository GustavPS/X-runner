//
// Created by gustav on 2016-11-16.
//

#include "Platform.h"


Platform::Platform(int x, int y)
    : x{x}, y{y}
{}

void Platform::add_block(Block block)
{
    if(blocks.size() > 1)
    {
        block.setX(blocks.back().getX() + block.getWidth());
    }
    else
    {
        block.setX(x);
    }
    block.setY(y);
    blocks.push_back(block);
}

void Platform::draw_horizontal(sf::RenderWindow & window)
{
    for(std::size_t i {}; i < blocks.size(); ++i)
    {
        blocks.at(i).draw(window);
    }
}