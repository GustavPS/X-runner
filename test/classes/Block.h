//
// Created by gustav on 2016-11-16.
//

#ifndef SFML_BLOCK_H
#define SFML_BLOCK_H
#include "SFML/Graphics.hpp"

class Block {
private:
    float x;
    float y;
    int width;
    int height;
    sf::RectangleShape rectangle {};

public:
    Block(float x, float y, int width, int height);
    Block(int width, int height);
    void moveX(int addX);
    void moveY(int addY);
    void setX(int newX);
    void setY(int newY);

    void draw(sf::RenderWindow & window);

    float getX() {return x;};
    float getY() {return y;};
    int getWidth() {return width;};
    int getHeight() {return height;};
    sf::RectangleShape get_shape() const {return rectangle;};
};


#endif //SFML_BLOCK_H
