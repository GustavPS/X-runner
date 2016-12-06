#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Object
{
    public:
        Object(const sf::Vector2f&, const sf::Vector2f&, const std::string&);
        virtual ~Object() noexcept = default;
        sf::Vector2f position;
        sf::Vector2f dimensions;
        std::string name;
        sf::RectangleShape shape;
        virtual void iamnull() = 0;
    
    private:
        //sf::Vector2f dimensions;
};

#endif