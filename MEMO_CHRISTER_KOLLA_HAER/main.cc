#include <SFML/Graphics.hpp>

#include "engine.h"

int main()
{    
    sf::RenderWindow window(
        sf::VideoMode(1920, 1080), "X Runner", sf::Style::Fullscreen);
    
    Engine engine;

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

        engine.simulate();
        engine.render(window);
    }
}