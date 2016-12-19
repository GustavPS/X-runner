#ifndef GRAVITABLE_H
#define GRAVITABLE_H

#include "movable_object.h"

class Gravitating_Object : public Movable_Object
{
    public:
      /*!
         \brief "Constructor"
         \param position "Position of the object"
         \param size "Size of the object"
         \param type "Type of the object"
         \param solid "If the object is solid"
         \param texture "Texture of the object""
      */
        Gravitating_Object(const sf::Vector2f&,
                           const sf::Vector2f&,
                           const std::string&,
                           const bool = false,
                           const sf::Texture* = nullptr);

        // Simulation
        /*!
           \brief "Prepares simulation of object"
           \param distance_modifier "Delta since last simulation-sequence"
           \param gravity_constant "How much high the gravity is"
           \return "Simulation cycles required by this object this simulation-sequence"
        */
        int prepare_simulate(const float,
                             const float);

    protected:
        // State : general
        sf::Clock m_gravity_clock;

        // Collision handling
        /*!
           \brief "Handles collision while the object have movement"
           \param object "Colliding object"
           \param steps "Steps taken in this movement"
        */
        virtual void handle_moving_collision(const Object*,
                                      const sf::Vector2f&) override;
};

#endif
