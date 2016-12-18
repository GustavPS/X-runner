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
        virtual ~State() noexcept;

        // Simulation : pure virtual
        virtual void prepare_simulate() = 0;
        virtual int simulate() = 0;

        // View : pure virtual
        virtual void set_view(sf::View&) = 0;

        // Getters : defined
        const sf::Sprite& get_background() const;
        const std::vector<const Object*>& get_texturated_objects() const;
        std::unordered_map<std::string, sf::Text>& ref_text_objects();
    
    protected:
        // Textures & background
        std::unordered_map<std::string, sf::Texture*> textures;
        sf::Texture background_texture;
        sf::Sprite background;

        // Objects
        std::vector<const Object*> objects;
        std::vector<const Object*> texturated_objects;
        std::unordered_map<std::string, sf::Text> text_objects;

        // Reset : defined
        virtual void soft_reset(); 
};

#endif