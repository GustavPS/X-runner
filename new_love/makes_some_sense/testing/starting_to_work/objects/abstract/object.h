#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Object
{
    public:
        // Constructors & destructors
        Object(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&);
        virtual ~Object() noexcept = default;

        // Getters
        sf::Vector2f get_position() const;
        sf::Vector2f get_dimensions() const;
        sf::RectangleShape get_shape() const;
    
    private:
        // Attributes
        sf::Vector2f position;
        std::string type;
        sf::Vector2f dimensions;
        sf::RectangleShape shape;
        
};

#endif