#include "engine.h"

Engine::Engine()
    : menu_state { new Menu_State {} }
    , game_state { new Game_State {} }
    , active_state { menu_state }
{}

void Engine::simulate()
{
    switch (active_state->simulate())
    {
        case 1:
            active_state = menu_state;
            break;
        case 2:
            if (std::string level = menu_state->selection != "return")
                game_state->load_level(level);
            active_state = game_state;
            break;
    }
}

void Engine::render(sf::RenderWindow& window)
{
    std::vector<sf::RectangleShape> shapes { active_state->get_visible_objects() };
    for (const auto shape : shapes)
    {
        window.render(shape);
    }
}