#include "engine.h"

Engine::Engine()
    : menu_state { new Menu_State {} }
    , game_state { new Game_State {} }
    , active_state { menu_state }
    , view { sf::FloatRect(0, 0, 1920, 1080) }
{
    view.zoom(0.75); // Quickfix, optimally our images should be 25% larger
    active_state->prepare_simulate();
}

Engine::~Engine()
{
    delete menu_state;
    delete game_state;
}

void Engine::simulate(sf::RenderWindow& window)
{
    switch (active_state->simulate())
    {
        case 0:
            break;
        case 1:
            active_state = menu_state;
            active_state->prepare_simulate();
            break;
        case 2:
            active_state = game_state;
            active_state->prepare_simulate();
            break;
        case 3:
            window.close();
            break;
    }
}

void Engine::render(sf::RenderWindow& window)
{
    window.clear();
    
    active_state->set_view(view);

    window.setView(view);

    window.draw(active_state->get_background());

    // Draw texturated_objects
    const auto &texturated_objects
        { active_state->get_texturated_objects() };

    for (auto *texturated_object : texturated_objects)
        window.draw(texturated_object->get_shape());

    // Draw text_objects
    auto &text_objects
        { active_state->ref_text_objects() };

    auto elapsed_time_it = text_objects.find("elapsed_time");
    if (elapsed_time_it != text_objects.end())
    {
        elapsed_time_it->second.setPosition(
            window.mapPixelToCoords(
                sf::Vector2i(0, 0)));
        
        window.draw(elapsed_time_it->second);
    }

    auto record_time_it = text_objects.find("record_time");
    if (record_time_it != text_objects.end())
    {
        record_time_it->second.setPosition(
            window.mapPixelToCoords(
                sf::Vector2i(
                    window.getSize().x
                    - record_time_it->second.getLocalBounds().width
                    - 60
                    , 0)));

        window.draw(record_time_it->second);
    }

    /*sf::Font font;
    font.loadFromFile("resources/fonts/3x5/3X5_____.TTF");
    sf::Text text { "hejsan", font, 40 };
    text.setFont(font);
    text.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x - text.getLocalBounds().width - 60, 0)));
    text.setColor(sf::Color::Red);
    window.draw(text);*/
    //record_sprite.setPosition(window.convertCoords(sf::Vector2i(0, 0)));
    //window.draw(record_sprite);
    
    window.display();
}