#ifndef BOMB_BIRD_H
#define BOMB_BIRD_H

#include "slow_bird.h"

class Bomb_Bird final : public Slow_Bird
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
           \param nfbb_texture "Texture of NFBB-objects spawned by the object"
        */
        Bomb_Bird(const sf::Vector2f&,
                   const sf::Vector2f&,
                   const std::string&,
                   const sf::Texture*,
                   const float,
                   const int,
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
        // Constants : textures
        const sf::Texture *m_nfbb_texture;

        // State : general
        sf::Clock m_nfbb_clock;
};

#endif
