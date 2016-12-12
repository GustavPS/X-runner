#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable.h"

class Movable_Object : public Simulatable
{
    public:
        // Constructors & destructors
        Movable_Object(const sf::Vector2f&,
                       const sf::Vector2f&,
                       const std::vector<std::string>&,
                       float);

        int prepare_simulate(const float);

        // Execute simulation of object : NOT overriding pure virtual
        void simulate(const int,
                      std::vector<Object*>&);

        virtual void end_simulate() override;

    protected:
        // State
        float speed;
        sf::Vector2f distance;

        // Collision handling : overriding null-defined
        virtual bool handle_collision(Object*,
                                      const sf::Vector2f&) override;

    private:
        // Move object
        void set_position(const sf::Vector2f&);
        void set_position(float, float);
};

#endif