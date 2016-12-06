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
        case 0:
            break;
        case 1:
            active_state = menu_state;
            break;
        case 2:
            if (std::string level = menu_state->selection != "return")
                game_state->load_level(level);
            game_state->clock.restart();
            active_state = game_state;
            break;
    }
}

void Engine::render(sf::RenderWindow& window)
{
    window.render(active_state->get_background());

    std::vector<Objects*> texturated_objects
        { active_state->get_texturated_objects() };
    for (const auto texturated_object : texturated_objects)
    {
        window.render(texturated_object->get_shape());
    }
    
    window.display();
}