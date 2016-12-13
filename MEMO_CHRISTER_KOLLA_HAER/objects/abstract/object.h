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
               const std::vector<std::string>&);
        virtual ~Object() noexcept = default;
        // ^ NOTE: Should probably be implemented in a more meaningful way

        // Getters
        sf::RectangleShape get_shape() const;
        std::vector<std::string> get_types() const;
        bool get_delete_status() const;
    
    protected:
        // State
        sf::RectangleShape shape;
        std::vector<std::string> types;
        bool m_delete_status {};
        
};

#endif