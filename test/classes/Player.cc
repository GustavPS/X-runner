//
// Created by gustav on 2016-11-15.
//

#include "Player.h"
#include "SFML/Graphics.hpp"

void Player::draw(sf::RenderWindow & window)
{
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
    window.draw(shape);
}

void Player::moveX(float addX)
{
    x += addX;
}

void Player::move(float addX, float addY)
{
    x += addX;
    y += addY;
}

sf::CircleShape Player::getShape() const
{
    return shape;
}