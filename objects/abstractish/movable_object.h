#ifndef MOVABLE_H
#define MOVABLE_H

#include "simulatable_object.h"

class Movable_Object : public Simulatable_Object
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor"
           \param position "Position of the object"
           \param size "Size of the object"
           \param type "Type of the object"
           \param solid "If the object is solid"
           \param texture "Texture of the object""
        */
        Movable_Object(const sf::Vector2f&,
                       const sf::Vector2f&,
                       const std::string&,
                       const bool = false,
                       const sf::Texture* = nullptr);

        // Simulation
        /*!
           \brief "Prepares simulation of object"
           \param distance_modifier "Delta since last simulation-sequence"
           \return "Simulation cycles required by this object this simulation-sequence"
        */
        int prepare_simulate(const float);
        /*!
           \brief "Executes simulation of object"
           \param simulation_cycles "Number simulation_cycles the object will be subjected this simulation-sequence"
           \param objects "Objects to check for collision with"
           \return "New objects spawned by this object"
        */
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override;
        /*!
           \brief "Executes end-of-simulation logic of object"
           \param objects "Objects to check for collision with""
        */
        virtual void end_simulate(const std::vector<const Object*> &objects) override;

    protected:
        // State : simulation
        sf::Vector2f m_distance;

        // State : collision
        bool m_ground_collision {};
        bool m_roof_collision {};
        bool m_wall_collision {};

        // Collision handling
        /*!
           \brief "Handles collision while the object have movement"
           \param object "Colliding object"
           \param steps "Steps taken in this movement"
        */
        virtual void handle_moving_collision(const Object*, const sf::Vector2f&);
        /*!
           \brief "Resets collision variables"
        */
        virtual void collision_state_cleanup();
        /*!
           \brief "Handles collision while the object does not have movement"
           \param object "Colliding object"
        */
        virtual void handle_static_collision(const Object*) {};
        /*
           \brief "Execute end-of-collision actions based on what have or havn't been collided
                   with in the previous collision-handlings"
        */
        virtual void handle_end_collision() {}

};

#endif
