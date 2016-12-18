#include <SFML/Graphics.hpp>

#include "engine/engine.h"

int main()
{
    Engine engine;

    sf::RenderWindow window(
        sf::VideoMode(1920, 1080), "Where the f_ are the birds at?", sf::Style::Fullscreen);

    window.setVerticalSyncEnabled(true);
    
    window.setMouseCursorVisible(false);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        engine.simulate(window);
        engine.render(window);
    }
}