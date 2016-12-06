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

        if (auto casted = dynamic_cast<Movable*>(object) != nullptr)
            movables.push_back(casted);

        if (auto casted = dynamic_cast<Player*>(object) != nullptr)
            player = casted;

        else if (auto casted = dynamic_cast<NPC*>(object) != nullptr)
            npcs.push_back(casted);

        else if (auto casted = dynamic_cast<Wall*>(object) != nullptr)
            walls.push_back(casted);

        else if (auto casted = dynamic_cast<Ground*>(object) != nullptr)
            grounds.push_back(casted);

        else if (auto casted = dynamic_cast<Wall*>(object) != nullptr)
            roofs.push_back(casted);
    }

    objects = std::make_tuple(level_parser.get_walls(),
                              level_parser.get_grounds(),
                              level_parser.get_roofs(),
                              level_parser.get_npcs(),
                              level_parser.get_player());

    for (const auto object_type : objects)
        for (const auto object : object_type)
        {
            if (object->get_shape()->getTexture() != nullptr);
                texturated_objects.push_back(object);
            if (auto casted = dynamic_cast<Movable*>(object) != nullptr)
                movable_objects.push_back(casted);
        }
}

int Game_State::simulate() override
{
    player->steps.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player->steps.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player->steps.x = 1;
    if (player->can_jump() && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player->start_jump();
       /* player->jumping = true;
        player->can_jump = false;*/
    
    if (player->is_jumping())
        player->adjust_jump();

    /*if(player->jumping)
    {
        if(player->steps.y < -2.5)
        {
            player->steps.y -= 0.8;
        }
        else
        {
            player->jumping = false;
        }
    }*/

    float distance_modifier
        { (clock.restart().asMilliseconds() / 1000.0f) };

    for (auto object : movable_objects)
    {
        if (!object->try_move(distance_modifier, gravity_modifier, objects))
            object->handle_collisions()
    }




    for (auto object : movables)
        object->move(distance_modifier, gravity_modifier)
}

/*Game_State::~Game_State()
{
    reset();
}*/

void Game_State::reset() override
{
    State::reset();
    walls.clear();
    grounds.clear();
    roofs.clear();
    npcs.clear();
    player = nullptr;
    gravitables.clear();
}