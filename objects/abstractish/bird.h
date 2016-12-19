#ifndef BIRD_H
#define BIRD_H

#include "../abstractish/movable_object.h"

class Bird : public Movable_Object
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor"
           \param position "Position of the object"
           \param size "Size of the object"
           \param type "Type of the object"
           \param texture "Texture of the object"
           \param speed "Speed of the object"
           \param direction "Direction of the object"
           \param cooldown "How long the objects opacity is 0.5"
           \param solid "If the object is solid"
        */
        Bird(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::string&,
             const sf::Texture*,
             const float,
             const int,
             const float,
             const bool = false);

        // Simulation
        /*!
           \brief "Prepares simulation of object"
           \param distance_modifier "Delta since last simulation-sequence"
           \param gravity_constant "How much high the gravity is"
           \return "Simulation cycles required by this object this simulation-sequence"
        */
        virtual int prepare_simulate(const float,
                                     const float) override final;

    protected:
        // Constants : Attributes
        const float m_speed;
        const float m_cooldown;

        // State : general
        int m_direction;

        // State : buffs & debuffs
        sf::Clock m_player_clock;
        bool m_player_debuff {};

        // Collision handling : overriding defined : final
        /*!
           \brief "Handles collision while the object have movement"
           \param object "Colliding object"
           \param steps "Steps taken in this movement"
        */
        virtual void handle_moving_collision(const Object*,
                                      const sf::Vector2f&) override final;

        /*!
           \brief "Handles collision while the object does not have movement"
           \param object "Colliding object"
        */
        virtual void handle_static_collision(const Object*);
};

#endif
