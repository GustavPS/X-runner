#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

class Object
{
    public:
        // Constructors & destructors
        Object(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::vector<std::string>&); // NOTE: Type+Subtype kanske ska vara ett pair ist
        virtual ~Object() noexcept = default;
        // ^ NOTE: Should probably be implemented in a more meaningful way

        // Getters
        sf::RectangleShape get_shape() const;

        // Pure virtual functions
        // NOTE: NEED A PURE VIRTUAL FUNCTION
    
    protected:
        // Attributes
        sf::Vector2f position;
        sf::RectangleShape shape;

        // Getters
        std::vector<std::string> get_types() const;

    private:
        // Attributes
        std::vector<std::string> types;
        
};

#endif