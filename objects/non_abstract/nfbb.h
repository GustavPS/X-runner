#ifndef NFBB_H
#define NFBB_H

#include "../abstractish/gravitating_object.h"

class NFBB final : public Gravitating_Object
{
    public:
        // Constructors & destructors
        /*!
           \brief "Constructor"
           \param position "Position of the object"
           \param size "Size of the object"
           \param type "Type of the object"
           \param texture "Texture of the object"
        */
        NFBB(const sf::Vector2f&,
             const sf::Vector2f&,
             const std::string&,
             const sf::Texture*);

        // Simulation
        /*!
           \brief "Executes simulation of object"
           \param simulation_cycles "Number simulation_cycles the object will be subjected this simulation-sequence"
           \param objects "Objects to check for collision with"
           \return "New objects spawned by this object"
        */
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) override final;

    private:
        // State : general
        bool m_on_ground {};
        sf::Clock m_despawn_clock;

        // Collision handling
        /*!
           \brief "Handles collision while the object does not have movement"
           \param object "Colliding object"
        */
        virtual void handle_static_collision(const Object*) override final;
        /*!
           \brief "Execute end-of-collision actions based on what have or havn't been collided
                   with in the previous collision-handlings"
        */
        virtual void handle_end_collision() override final;
};

#endif
