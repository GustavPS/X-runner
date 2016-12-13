#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable.h"

class Movable_Object : public Simulatable
{
    public:
        // Constructors & destructors
        Movable_Object(const sf::Vector2f&,
                       const sf::Vector2f&,
                       const std::vector<std::string>&);

        int prepare_simulate(const float);

        // Execute simulation of object : overriding pure virtual
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override;

        // Clean-up simulation state
        virtual void end_simulate(const std::vector<const Object*> &objects) override;

    protected:
        // Simulation state
        sf::Vector2f distance;

        // Collision handling : overriding null-defined
        virtual bool handle_collision(const Object*,
                                      const sf::Vector2f&) override;
};

#endif