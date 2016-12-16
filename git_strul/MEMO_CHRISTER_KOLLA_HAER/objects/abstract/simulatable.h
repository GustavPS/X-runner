#ifndef SIMULATABLE_H
#define SIMULATABLE_H

#include "object.h"

class Simulatable : public Object
{
    public:
        // Constructors & destructors
        Simulatable(const sf::Vector2f&,
                    const sf::Vector2f&,
                    const std::string&,
                    const bool = false,
                    const sf::Texture *const = nullptr);

        // Prepare and calculate the required amount of simulations 
        // : pure virtual
        virtual int prepare_simulate(const float,
                                     const float) = 0;

        // Execute simulation of object : pure virtual
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) = 0;
        
        // Clean-up simulation state : null-defined
        virtual void end_simulate(const std::vector<const Object*> &objects) {}

    protected:
        // Collision detection
        // : defined
        virtual const std::vector<const Object*> get_colliding_objects(
            const std::vector<const Object*>&) const;
};

#endif