#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Object
{
    public:
        // Constructors & destructors
        Object(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&,
               const bool = false);
        virtual ~Object() noexcept = default;
        // ^ NOTE: Should probably be implemented in a more meaningful way

        // Getters
        std::string get_type() const;
        bool is_solid() const;
        bool get_delete_status() const;
        sf::RectangleShape get_shape() const;
    
    protected:
        // Constants : attributes
        const std::string type;

        // State : attributes
        bool solid {};

        // State : general
        bool m_delete_status {};
        sf::RectangleShape shape;
        
};

#endif