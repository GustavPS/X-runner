#ifndef NFBB_H
#define NFBB_H

#include "../abstract/gravitable.h"

class NFBB final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        NFBB(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::string&);

        // Execute simulation of object : overriding defined : final
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override final;

    private:
        // State : general
        bool on_ground {};
        sf::Clock despawn_clock;

        // Collision handling : overriding defined : final
        virtual void handle_collision(const Object*, const sf::Vector2f&) override final;
};

#endif