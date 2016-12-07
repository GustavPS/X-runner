#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable.h"

class Movable : public Simulatable
{
    public:
        // Constructors & destructors
        Movable(const sf::Vector2f&,
                const sf::Vector2f&,
                const std::string&,
                float);

    protected:
        // Attributes
        float speed;

        // Moving
        void Movable::move(const sf::Vector2f&,
                           const std::vector<Object*>&);
        void set_position(const sf::Vector2f&);
        void set_position(float, float);

        // State
        std::unordered_set<std::string> collided_object_types;

    private:
        // Helper functions
        void check_collision(const sf::Vector2f&)
                             const std::vector<Object*>&);

        // Pure virtual functions
        virtual void handle_collision(Object&,
                                      const sf::Vector2f&) = 0;
        virtual void handle_null_collision() = 0;
        // ^ NOTE: kanske kan default implementeras som { /* do nothing */ } ist för pure virtual
};

#endif