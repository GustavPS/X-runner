//
// Created by gustav on 2016-11-16.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Block.h"

Block::Block(float x, float y, int width, int height)
    : x{x}, y{y}, width{width}, height{height}
{
    rectangle.setSize(sf::Vector2f(width, height));
}

Block::Block(int width, int height)
    : width{width}, height{height}
{
    rectangle.setSize(sf::Vector2f(width, height));
}

void Block::moveX(int addX)
{
    x += addX;
}
void Block::moveY(int addY)
{
    y += addY;
}

void Block::setX(int newX)
{
    x = newX;
}
void Block::setY(int newY)
{
    y = newY;
}

void Block::draw(sf::RenderWindow & window)
{
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(x, y);
    window.draw(rectangle);
}