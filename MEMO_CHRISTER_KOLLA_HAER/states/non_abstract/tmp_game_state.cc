#include "game_state.h"

typedef std::vector<Object*> objects;

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
    objects_size = objects.size();

    for (auto *object : objects)
    {
        if (object->get_shape().getTexture() != nullptr)
            texturated_objects.push_back(const_cast<Object*>(object));

        auto *simulatable_object = dynamic_cast<Simulatable*>(object);
        if (simulatable_object != nullptr)
            simulatable_objects.push_back(simulatable_object);

        auto *player_object = dynamic_cast<const Player*>(object);
        if (player_object != nullptr)
            player = player_object;
    }
}

int Game_State::simulate()
{
    // If new objects have been added, iterate over the new objects
    // and add them to <simulatable_objects> if they are simulatable
    if (objects.size() > objects_size)
    {
        for (auto it { objects.begin() + objects_size }; it != objects.end(); ++it)
        {
            auto *simulatable_object = dynamic_cast<Simulatable*>(*it);
            if (simulatable_object != nullptr)
                simulatable_objects.push_back(simulatable_object);
            ++objects_size;
        }
    }

    // Simulate simulatable objects
    // (If marked for deletion: remove from <simulatable_object>)
    int total_simulations {};

    float distance_modifier { (clock.restart().asMilliseconds() / 1000.0f) };

    for (auto it { simulatable_objects.begin() }; it != simulatable_objects.end(); ++it)
    {
        if ((*it)->get_delete_status())
        {
            simulatable_objects.erase(it);
        }
        else
        {
            int simulations
                { (*it)->prepare_simulate(
                             objects, distance_modifier, gravity_constant) };

            if (simulations > total_simulations)
                total_simulations = simulations;
        }
    }

    for (int i {}; i < total_simulations; ++i)
    {
        for (auto it { simulatable_objects.begin() };
             it != simulatable_objects.end(); ++it)
        {
            (*it)->simulate(total_simulations, objects);
        }
    }

    for (auto it { simulatable_objects.begin() };
         it != simulatable_objects.end(); ++it)
    {
        (*it)->end_simulate();
    }

    // Free memory of and remove objects marked for deletion from <objects>
    for (auto it { objects.cbegin() }; it != objects.cend(); ++it)
    {
        if ((*it)->get_delete_status())
        {
            delete *it;
            objects.erase(it);
            --objects_size;
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