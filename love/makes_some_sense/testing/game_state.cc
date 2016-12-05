#include "game_state.h"

Game_State::Game_State() {}

void Game_State::load_level(const std::string &level)
{
    reset();
    Level_Parser level_parser { level };
    objects = level_parser.get_objects();
}

int Game_State::simulate() override
{

}