#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable.h"

class Gravitating_Object : public Movable_Object
{
    public:
        // Constructors & destructors
        Gravitating_Object(const sf::Vector2f&,
                           const sf::Vector2f&,
                           const std::vector<std::string> &types);

        int prepare_simulate(const float,
                             const float);

        // Execute simulation of object : overriding pure virtual
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override;

        virtual void end_simulate(const std::vector<const Object*>&);

    protected:
        // State
        float weight;
        sf::Clock gravity_clock;

        // Collision handling : overriding null-defined
        virtual bool handle_collision(const Object*,
                                      const sf::Vector2f&) override;
};

#endif