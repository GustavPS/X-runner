#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable_object.h"

class Movable_Object : public Simulatable_Object
{
    public:
        // Constructors & destructors
        Movable_Object(const sf::Vector2f&,
                       const sf::Vector2f&,
                       const std::string&,
                       const bool = false,
                       const sf::Texture* = nullptr);

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
        sf::Vector2f m_distance;

        // State : collision
        bool m_ground_collision {};
        bool m_roof_collision {};
        bool m_wall_collision {};

        // Collision handling
        // : defined
        virtual void handle_moving_collision(const Object*, const sf::Vector2f&);
        virtual void collision_state_cleanup();
        // : null-defined
        virtual void handle_static_collision(const Object*) {};
        virtual void handle_end_collision() {}
        
};

#endif