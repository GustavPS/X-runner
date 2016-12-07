#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Object
{
    public:
        //constructors & destructors
        Object(const sf::Vector2f&, const sf::Vector2f&);

        virtual ~Object() noexcept = default;

        //getters
        sf::Vector2f get_position() const;
        sf::Vector2f get_dimensions() const;
        sf::RectangleShape get_shape() const;

        //setters
        void set_position(const sf::Vector2f&);
    
    private:
        std::string name;
        sf::Vector2f position;
        sf::Vector2f dimensions;
        sf::RectangleShape shape;
};

#endif