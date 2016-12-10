#include "game_state.h"

Game_State::Game_State() {}

void Game_State::load_level(const std::string &level)
{
    reset();
    Level_Parser level_parser { level };

    objects = level_parser.get_objects();

    for (const auto object : objects)
    {
        if (object->get_shape()->getTexture() != nullptr)
            texturated_objects.push_back(object);

        if (auto casted = dynamic_cast<Simulatable&>(object) != nullptr)
            simulatable_objects.push_back(casted);
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
            (*it)->simulate(distance_modifier, gravity_modifier, objects)
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
}

/*Game_State::~Game_State()
{
    reset();
}*/

void Game_State::reset()
{
    State::reset();
    simulatable_objects.clear();
}