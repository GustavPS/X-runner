#ifndef SIMULATABLE_OBJECT_H
#define SIMULATABLE_OBJECT_H

#include "object.h"

class Simulatable_Object : public Object
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
        Simulatable_Object(const sf::Vector2f&,
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
        virtual int prepare_simulate(const float,
                                     const float) = 0;
        /*!
           \brief "Executes simulation of object"
           \param simulation_cycles "Number simulation_cycles the object will be subjected this simulation-sequence"
           \param objects "Objects to check for collision with"
           \return "New objects spawned by this object"
        */
        virtual std::vector<Object*> simulate(const int,
                                              const std::vector<const Object*>&) = 0;
        /*!
           \brief "Executes end-of-simulation logic of object"
           \param objects "Objects to check for collision with""
        */
        virtual void end_simulate(const std::vector<const Object*> &objects) {}

    protected:
        // Collision detection
        /*!
           \brief "Get the collidion objects"
           \param std::vector<const Object*> "A vector with the objects to check collision with."
           \return "A vector with the colliding objects"
        */
        virtual const std::vector<const Object*> get_colliding_objects(
            const std::vector<const Object*>&) const;
};

#endif
