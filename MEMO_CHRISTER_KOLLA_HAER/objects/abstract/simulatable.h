#ifndef SIMULATABLE_H
#define SIMULATABLE_H

#include "object.h"

#include <unordered_set>

class Simulatable : public Object
{
    public:
        // Constructors & destructors
        Simulatable(const sf::Vector2f&,
                    const sf::Vector2f&,
                    const std::string&,
                    const bool = false);

        // Prepare and calculate the required amount of simulations 
        // : pure virtual
        virtual int prepare_simulate(const float,
                                     const float) = 0;

        // Execute simulation of object : pure virtual
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) = 0;
        
        // Clean-up simulation state : defined
        virtual void end_simulate(const std::vector<const Object*> &objects);

    protected:
        // Collision handling : defined
        void check_collision(const std::vector<const Object*>&,
                             const sf::Vector2f& = {});

        // Collision handling : null-defined
        virtual void handle_collision(const Object*,
                                      const sf::Vector2f& = {}) {}
        virtual void handle_end_collision(const sf::Vector2f&) {}
        virtual void collision_state_cleanup() {}
};

#endif