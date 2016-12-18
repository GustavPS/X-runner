#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include "../../objects/abstractish/object.h"

#include <vector>
#include <unordered_map>
#include <string>

class State
{
    public:
        // Constructors & destructors
        /*!
           \brief "Virtual destructor which frees all resources owned by the state"
        */
        virtual ~State() noexcept;

        // Simulation
        virtual void prepare_simulate() = 0;
        virtual int simulate() = 0;

        // View
        virtual void set_view(sf::View&) = 0;

        // Getters
        /*!
           \return "Returns the background set in the state"
        */
        const sf::Sprite& get_background() const;
        /*!
           \return "Returns the texturated_objects owned by the state"
        */
        const std::vector<const Object*>& get_texturated_objects() const;
        /*!
           \return "Returns the text_objects owned by the state as a non-const reference"
        */
        std::unordered_map<std::string, sf::Text>& ref_text_objects();

    protected:
        // Textures & background & fonts
        std::unordered_map<std::string, sf::Texture*> textures;
        sf::Texture background_texture;
        sf::Sprite background;
        sf::Font font;

        // Objects
        std::vector<const Object*> objects;
        std::vector<const Object*> texturated_objects;
        std::unordered_map<std::string, sf::Text> text_objects;

        // Reset : defined
        virtual void soft_reset();
};

#endif
