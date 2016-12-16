#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

#include "../../objects/abstract/object.h"

#include <vector>

class State
{
    public:
        // Constructors & destructors
        virtual ~State() noexcept;

        // Getters
        sf::Sprite get_background() const;
        std::vector<const Object*> get_texturated_objects() const;

        // Pure virtual functions
        virtual int simulate() = 0;

        // Null-defined functions
        virtual void set_zoom(sf::View&) {};
        virtual void set_view(sf::View&) {};
    
    protected:
        // Objects
        sf::Sprite background;
        std::vector<const Object*> objects;
        std::vector<const Object*> texturated_objects;

        // Resetting the state
        virtual void reset(); 
};

#endif