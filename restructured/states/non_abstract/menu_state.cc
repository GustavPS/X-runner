#include "menu_state.h"

#include "../../level_parser/level_parser.h"

Menu_State::Menu_State()
{
    textures["player"] = new sf::Texture;
    textures["player"]->loadFromFile("resources/object_sprites/player.png");
}

void Menu_State::prepare_simulate()
{
    soft_reset();

    /******************************************************/
    /* Hardcoded for now, havn't bothered to build with several levels in mind at this stage */
    Level_Parser level_parser { "resources/levels/level_0/map.tmx" };

    background_texture.loadFromFile("resources/levels/level_0/background.png");
    background_texture.setSmooth(true);
    background.setTexture(background_texture);

    gravity_constant = 9.82;
    /*****************************************************/

    auto tmp_objects { level_parser.get_objects(textures) };

    for (auto *tmp_object : tmp_objects)
    {
        objects.push_back(tmp_object);

        if (tmp_object->get_shape().getTexture() != nullptr)
            texturated_objects.push_back(tmp_object);

        auto *player_object { dynamic_cast<Player*>(tmp_object) };
        if (player_object != nullptr)
            player = player_object;
    }

    delta_clock.restart();
}

int Menu_State::simulate()
{
    // Time elapsed since last simulation of player
    float distance_modifier { (delta_clock.restart().asMilliseconds() / 1000.0f) };

    // Prepare simulation of the player and get the number of simulation cycles needed
    int simulation_cycles
        { player->prepare_simulate(
            distance_modifier, gravity_constant) };

    // Simulate the player * simulation_cycles times
    for (int _ {}; _ < simulation_cycles; ++_)
        player->simulate(simulation_cycles, objects);


    // Let the player perform its end-of-simulation code
    player->end_simulate(objects);

    // Return action corresponding to players out-of-game action variable, or 0
    const std::string oog_action { player->get_oog_action() };
    if (oog_action == "play")
    {
        return 2;
    }
    else if(oog_action == "quit")
    {
        return 3;
    }

    return 0;
}

void Menu_State::set_view(sf::View &view)
{
    view.setCenter(player->get_shape().getPosition()
                   + player->get_shape().getSize());
}

void Menu_State::soft_reset()
{
    player = nullptr;
    State::soft_reset();
}