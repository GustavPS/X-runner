//
// Created by gustav on 2016-11-15.
//

#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

class Player {
private:
    float x;
    float y;
    sf::CircleShape shape {50};


public:
    Player(float x, float y)
            : x{x}, y{y}
    {};
    void move(float addX, float addY);
    void moveX(float addX);
    void moveY(float addY);
    void draw(sf::RenderWindow & window);

    float getX() {return x;}
    float getY() {return y;}

    sf::CircleShape getShape() const;
};


#endif //SFML_PLAYER_H
