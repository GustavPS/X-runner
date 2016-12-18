#ifndef PLAYER_H
#define PLAYER_H

#include "../abstractish/gravitating_object.h"

#include <unordered_set>

class Player final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        Player(const sf::Vector2f&,
               const sf::Vector2f&,
               const std::string&,
               const sf::Texture*,
               const float);

        // Prepare and calculate the required amount of simulations 
        // : overriding defined : final
        virtual int prepare_simulate(const float,
                                     const float) override final;

        const std::string& get_oog_action() const;

    private:
        // Constants : attributes
        const float m_speed;

        // State : general
        bool m_jumping {};
        bool m_on_ground {};

        // State : buffs & debuffs
        sf::Clock m_slow_bird_clock;
        std::unordered_set<const Object*> m_slow_bird_debuffs;

        sf::Clock m_boost_bird_clock;
        std::unordered_set<const Object*> m_boost_bird_buffs;

        sf::Clock m_nfbb_clock;
        std::unordered_set<const Object*> m_nfbb_debuffs;

        bool m_quicksand_debuff {};

        // State : collision
        bool m_quicksand_collision {};

        // State : out-of-game actions
        std::string m_oog_action;

        // Collision handling : overriding defined : final
        virtual void handle_moving_collision(const Object*, const sf::Vector2f&) override final;

        virtual void handle_static_collision(const Object*) override final;

        virtual void collision_state_cleanup() override final;

        // Collision handling : overriding null-defined : final
        virtual void handle_end_collision() override final;
};

#endif