#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>

#include <string>

class Object
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor"
           \param position "Position of the object"
           \param size "Size of the object"
           \param type "Type of the object"
           \param solid "If the object is solid"
           \param texture "Texture of the object""
        */
        Object(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&,
               const bool = false,
               const sf::Texture* = nullptr);
        /*!
           \brief "Virtual destrucor = default"
        */
        virtual ~Object() noexcept = default;

        // Getters
        /*!
           \return "Type of object"
        */
        std::string get_type() const;
        /*!
           \return "If object is solid"
        */
        bool is_solid() const;
        /*!
           \return "If object is marked for deletion"
        */
        bool get_delete_status() const;
        /*!
           \brief "Returns the object's shape, which is used for drawing as well
                   as getting the objects position and size"
           \return "Shape of object"
        */
        sf::RectangleShape get_shape() const;

    protected:
        // Constants : textures
        const sf::Texture *m_texture;

        // Constants : attributes
        const std::string m_type;

        // State : attributes
        bool m_solid {};

        // State : general
        bool m_delete_status {};
        sf::RectangleShape m_shape;

};

#endif
