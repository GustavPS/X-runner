#ifndef NFBB_H
#define NFBB_H

#include "../abstract/gravitable.h"

class NFBB final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        NFBB(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::vector<std::string> &types);

        // Execute simulation of object : overriding pure virtual : final
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override final;

    private:
        // State
        bool on_ground {};
        sf::Clock despawn_clock;

        // Collision handling : overriding null-defined : final
        virtual bool handle_collision(const Object*, const sf::Vector2f&) override final;
};

#endif