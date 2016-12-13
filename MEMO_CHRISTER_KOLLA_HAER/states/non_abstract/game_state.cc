#include "game_state.h"

Game_State::~Game_State()
{
    reset();
}

void Game_State::load_level(const std::string &level)
{
    reset();

    Level_Parser level_parser { level };

    sf::Texture bgTexture;
    bgTexture.loadFromFile("new.png");
    bgTexture.setSmooth(false);
    background = bgTexture;

    gravity_modifier = 1;

    auto tmp_objects = level_parser.get_objects();
    objects.insert(objects.end(), tmp_objects.begin(), tmp_objects.end());

    for (const auto object : objects)
    {
        if (object->get_shape().getTexture() != nullptr)
            texturated_objects.push_back(object);

        auto simulatable_object = dynamic_cast<Simulatable&>(object);
        if (simulatable_object != nullptr)
            simulatable_objects.push_back(simulatable_object);

        auto player_object = dynamic_cast<Player*>(object);
        if (player_object != nullptr)
            player = player_object;
    }
}

int Game_State::simulate()
{
    float distance_modifier { (clock.restart().asMilliseconds() / 1000.0f) };

    for (auto it { simulatable_objects.begin() }; it != simulatable_objects.end(); ++it)
    {
        if (*it == nullptr)
        {
            simulatable_objects.erase(it);
        }
        else
        {
            (*it)->simulate(distance_modifier, gravity_modifier, objects);
        }
    }
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