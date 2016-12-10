#include "game_state.h"

Game_State::~Game_State()
{
    reset();
}
#include <iostream>
void Game_State::load_level(const std::string &level)
{
    reset();

    Level_Parser level_parser { level };
    sf::Texture bgTexture;
    if(!bgTexture.loadFromFile("new.png"))
        std::cerr << "Du suger kuk!";
    background.setTexture(bgTexture);

    gravity_constant = 9.82;

    objects = level_parser.get_objects();

    for (auto object : objects)
    {
        if (object->get_shape().getTexture() != nullptr)
            texturated_objects.push_back(object);

        auto simulatable_object = dynamic_cast<Simulatable*>(object);
        if (simulatable_object != nullptr)
            simulatable_objects.push_back(simulatable_object);

        auto player_object = dynamic_cast<Player*>(object);
        if (player_object != nullptr)
            player = player_object;
    }
}

int Game_State::simulate()
{
    // Simulate simulatable objects
    float distance_modifier { (clock.restart().asMilliseconds() / 1000.0f) };
    for (auto it { simulatable_objects.begin() }; it != simulatable_objects.end(); ++it)
    {
        if ((*it)->m_delete == true)
        {
            simulatable_objects.erase(it);
        }
        else
        {
            (*it)->simulate(objects, distance_modifier, gravity_constant);
        }
    }

    // Cleanup deleted objects
    for (auto it { objects.begin() }; it != objects.end(); ++it)
    {
        if ((*it)->m_delete == true)
        {
            delete *it;
            objects.erase(it);
        }
    }

    return 0;
}

void Game_State::set_zoom(sf::View &view)
{
    view.zoom(0.5);
}

void Game_State::set_view(sf::View &view)
{
    view.setCenter(player->get_position() + player->get_shape().getSize());
}

void Game_State::reset()
{
    State::reset();
    simulatable_objects.clear();
    player = nullptr;
}