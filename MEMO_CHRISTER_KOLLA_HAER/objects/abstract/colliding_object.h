#ifndef COLLIDING_OBJECT_H
#define COLLIDING_OBJECT_H

#include "simulatable.h"

class Colliding_Object : public Simulatable
{
    public:
        // Constructors & destructors
        Colliding_Object(const sf::Vector2f&,
                         const sf::Vector2f&,
                         const std::string&,
                         const bool = false);
        
        // Clean-up simulation state : overriden null-defined
        virtual void end_simulate(const std::vector<const Object*> &objects);

    protected:
        // Collision handling
        // : defined
        void check_collision(const std::vector<const Object*>&,
                             const sf::Vector2f& = {});
        // : pure virtual
        virtual void handle_collision(const Object*,
                                      const sf::Vector2f& = {}) = 0;
        // : null-defined
        virtual void handle_end_collision(const sf::Vector2f&) {}
        virtual void collision_state_cleanup() {}
};

#endif