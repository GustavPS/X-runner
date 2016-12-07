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
               const std::string&,
               const std::string& = "");
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
        std::string get_type() const;
        std::string get_subtype() const;

    private:
        // Attributes
        std::string type;
        std::string subtype;
        
};

#endif