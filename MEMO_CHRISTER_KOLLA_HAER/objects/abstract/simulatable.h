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
                    const std::vector<std::string>&);

        // Prepare and calculate the required amount of simulations
        //     : null-defined
        virtual int prepare_simulate(std::vector<Object*>&,
                                     const float,
                                     const float) { return 1; }

        // Execute simulation of object : pure virtual
        virtual void simulate(int,
                              std::vector<Object*>&) = 0;
        
        // Clean-up after simulations : null-defined
        virtual void end_simulate() {}

    protected:
        // State
        std::unordered_set<std::string> collided_object_types;

        // Collision handling
        void check_collision(std::vector<Object*>&,
                             const sf::Vector2f& = {},
                             const bool = true);

        // Collision handling : null-defined
        virtual bool handle_collision(Object*,
                                      const sf::Vector2f& = {}) { return {}; }

        virtual void handle_end_collision(const sf::Vector2f&) {}
};

#endif