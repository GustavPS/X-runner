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
               const bool = false,
               const sf::Texture *const = nullptr);

        virtual ~Object() noexcept = default;

        // Getters
        std::string get_type() const;
        bool is_solid() const;
        bool get_delete_status() const;
        sf::RectangleShape get_shape() const;
    
    protected:
        // Constants : textures
        const sf::Texture *const m_texture;

        // Constants : attributes
        const std::string m_type;

        // State : attributes
        bool m_solid {};

        // State : general
        bool m_delete_status {};
        sf::RectangleShape m_shape;
        
};

#endif