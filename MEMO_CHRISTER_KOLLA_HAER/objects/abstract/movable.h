#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable.h"

class Movable_Object : public Simulatable
{
    public:
        // Constructors & destructors
        Movable_Object(const sf::Vector2f&,
                       const sf::Vector2f&,
                       const std::string&,
                       const bool = false);

        // Prepare and calculate the required amount of simulations 
        // : overriding pure virtual
        int prepare_simulate(const float);

        // Execute simulation of object : overriding pure virtual
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override;

        // Clean-up simulation state : overriding defined
        virtual void end_simulate(const std::vector<const Object*> &objects) override;

    protected:
        // State : simulation
        sf::Vector2f distance;

        // State : collision
        bool m_ground_collision {};
        bool m_roof_collision {};
        bool m_wall_collision {};

        // Collision handling : overriding null-defined
        virtual void handle_collision(const Object*, const sf::Vector2f&) override;
        virtual void collision_state_cleanup() override;
};

#endif