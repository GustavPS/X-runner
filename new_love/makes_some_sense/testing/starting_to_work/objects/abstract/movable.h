#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable.h"

class Movable : public Simulatable
{
    public:
        //constructors & destructors
        Movable(const sf::Vector2f&,
                const sf::Vector2f&,
                const std::string&,
                float);

    protected:
        void Movable::move(const sf::Vector2f&,
                           const std::vector<Object*>&);

        //setters
        void set_position(const sf::Vector2f&);
        void set_position(float, float);

    private:
        float speed;

        void check_collision(const sf::Vector2f&)
                             const std::vector<Object*>&);

        virtual void handle_collision(Object&,
                                      const sf::Vector2f&) = 0;
};

#endif