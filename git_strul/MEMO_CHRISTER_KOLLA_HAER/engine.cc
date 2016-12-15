#include "engine.h"

Engine::Engine()
    : menu_state { new Menu_State {} }
    , game_state { new Game_State {} }
    , active_state { menu_state }
    , view { sf::FloatRect(0, 0, 1920, 1080) }
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
    active_state->set_view(view);

    window.setView(view);

    window.draw(active_state->get_background());

    std::vector<Object*> texturated_objects
        { active_state->get_texturated_objects() };

    for (const auto object : texturated_objects)
    {
        auto s = object->get_shape();
        s.x = roundf(s.x);
        s.y = roundf(s.y);
        window.draw(s);
    }
    
    window.display();
}