#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include "../../objects/abstract/object.h"

#include <vector>
#include <unordered_map>

class State
{
    public:
        // Constructors & destructors
        virtual ~State() noexcept;

        // Getters
        const sf::Sprite& get_background() const;
        const std::vector<const Object*>& get_texturated_objects() const;

        // Pure virtual functions
        virtual int simulate() = 0;
        virtual void set_zoom(sf::View&) = 0;
        virtual void set_view(sf::View&) = 0;
    
    protected:
        // Objects
        std::unordered_map<std::string, sf::Texture*> textures;
        sf::Texture background_texture;
        sf::Sprite background;
        std::vector<const Object*> objects;
        std::vector<const Object*> texturated_objects;

        // Resetting the state
        virtual void reset(); 
};

#endif