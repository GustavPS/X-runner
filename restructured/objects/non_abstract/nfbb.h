#ifndef NFBB_H
#define NFBB_H

#include "../abstractish/gravitating_object.h"

class NFBB final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        NFBB(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::string&,
             const sf::Texture*);

        // Execute simulation of object : overriding defined : final
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override final;

    private:
        // State : general
        bool m_on_ground {};
        sf::Clock m_despawn_clock;

        // Collision handling : overriding defined : final
        virtual void handle_static_collision(const Object*) override final;
        
        // Collision handling : overriding null-defined : final
        virtual void handle_end_collision() override final;
};

#endif