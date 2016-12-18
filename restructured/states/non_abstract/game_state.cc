#include "game_state.h"

#include "../../level_parser/level_parser.h"

#include <algorithm>
#include <functional>

Game_State::Game_State()
{
    textures["player"] = new sf::Texture;
    textures["player"]->loadFromFile("resources/object_sprites/player.png");

    textures["slow_bird"] = new sf::Texture;
    textures["slow_bird"]->loadFromFile("resources/object_sprites/slow_bird.png");
    textures["slow_bird"]->setSmooth(true);

    textures["boost_bird"] = new sf::Texture;
    textures["boost_bird"]->loadFromFile("resources/object_sprites/boost_bird.png");
    textures["boost_bird"]->setSmooth(true);

    textures["bomb_bird"] = new sf::Texture;
    textures["bomb_bird"]->loadFromFile("resources/object_sprites/bomb_bird.png");
    textures["bomb_bird"]->setSmooth(true);

    textures["nfbb"] = new sf::Texture;
    textures["nfbb"]->loadFromFile("resources/object_sprites/nfbb.png");
    textures["nfbb"]->setSmooth(true);
}

void Game_State::prepare_simulate()
{
    soft_reset();

    /******************************************************/
    /* Hardcoded for now, havn't bothered to build with several levels in mind at this stage */
    Level_Parser level_parser { "resources/levels/level_1/map.tmx" };

    background_texture.loadFromFile("resources/levels/level_1/background.png");
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

        auto *simulatable_object
            { dynamic_cast<Simulatable_Object*>(tmp_object) };
        if (simulatable_object != nullptr)
            simulatable_objects.push_back(simulatable_object);

        auto *player_object { dynamic_cast<const Player*>(tmp_object) };
        if (player_object != nullptr)
            player = player_object;
    }

    delta_clock.restart();
    result_clock.restart();
}

int Game_State::simulate()
{
    // Time elapsed since last simulation of simulatable objects
    float distance_modifier { (delta_clock.restart().asMilliseconds() / 1000.0f) };

    // Number of simulations to run on each simulatable object
    int simulation_cycles {};

    // New objects generated by simulations
    std::vector<Object*> new_objects;

    // Size of <simulatable_objects>
    std::size_t stored_simulatable_objects_size
        { simulatable_objects.size() };

    // Prepare each simulatable object for simulation
    // and get the number of simulation cycles needed
    for (auto *simulatable_object : simulatable_objects)
    {
        int tmp_simulation_cycles
            { simulatable_object->prepare_simulate(
                                      distance_modifier, gravity_constant) };
        
        if (tmp_simulation_cycles > simulation_cycles)
        {
            simulation_cycles = tmp_simulation_cycles;
        }
    }

    // Simulate each simulatable object * simulation_cycles times
    // If a simulation generates new objects, add them to <new_objects>
    for (int _ {}; _ < simulation_cycles; ++_)
    {
        for (auto *simulatable_object : simulatable_objects)
        {
            auto tmp_new_objects
                { simulatable_object->simulate(simulation_cycles, objects) };

            if (!tmp_new_objects.empty())
            {
                new_objects.insert(new_objects.end(),
                                   tmp_new_objects.begin(),
                                   tmp_new_objects.end());
            }
        }
    }

    // Let each simulatable object perform its end-of-simulation code
    for (auto *simulatable_object : simulatable_objects)
        simulatable_object->end_simulate(objects);

    // Free memory of and remove objects marked for deletion from
    // <simulatable_objects>, <texturated_objects> and <objects>
    simulatable_objects.erase(
        std::remove_if(
            simulatable_objects.begin(),
            simulatable_objects.end(),
            std::mem_fn(&Simulatable_Object::get_delete_status)),
        simulatable_objects.end());

    if (simulatable_objects.size() < stored_simulatable_objects_size)
    {
        texturated_objects.erase(
            std::remove_if(
                texturated_objects.begin(),
                texturated_objects.end(),
                std::mem_fn(&Object::get_delete_status)),
            texturated_objects.end());

        objects.erase(
            std::remove_if(
                objects.begin(),
                objects.end(),
                [](auto *object)
                {
                    bool delete_status { object->get_delete_status() };

                    if (delete_status)
                        delete object;

                    return delete_status;
                }),
            objects.end());
    }

    // Add each new object to <objects>
    // and, if texturated, to <texturated_objects>
    // and, if simulatable, to <simulatable_objects>
    for (auto *new_object : new_objects)
    {
        objects.push_back(new_object);

        if (new_object->get_shape().getTexture() != nullptr)
            texturated_objects.push_back(new_object);
            
        auto *simulatable_object = dynamic_cast<Simulatable_Object*>(new_object);
        if (simulatable_object != nullptr)
            simulatable_objects.push_back(simulatable_object);
    }

    if (player->get_oog_action() == "goal")
    {
        return 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return 2;
    return 0;
}

void Game_State::set_view(sf::View &view)
{
    view.setCenter(player->get_shape().getPosition()
                   + player->get_shape().getSize());
}

void Game_State::soft_reset()
{
    player = nullptr;
    simulatable_objects.clear();
    State::soft_reset();
}