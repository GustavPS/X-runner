#include <SFML/Graphics.hpp>
#include "level_parser/level_parser.h"
#include "objects/player.h"
#include "objects/block.h"

//DEBUGGING
#include <iostream>

void delete_ptrs(std::vector<Object*> &objects)
{
    for (auto *object : objects)
    {
        delete object;
    }
}

int main()
{

    sf::Clock clock;
    sf::Time delta;

    sf::RenderWindow window(sf::VideoMode(1440, 960), "Hello World!");
    window.setVerticalSyncEnabled(true);

    float speed {250};
    float gravity {0.25};
    

    sf::Texture bgTexture;
    bgTexture.loadFromFile("new.png");
    sf::Sprite background { bgTexture };

    Level_Parser level_parser { "new.tmx" };

    std::vector<Object*> blocks { level_parser.get_blocks() };
    Player player { level_parser.get_player() };
    //Player *player { new Player { level_parser.get_player() } };

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

        int xsteps {};
        int ysteps {};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            xsteps -= 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            xsteps += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ysteps -= 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ysteps += 1;

        sf::Time delta { clock.restart() };
        {
            float distance { speed * (delta.asMilliseconds() / 1000.0f) };
            xsteps *= distance;
            ysteps *= distance;

            sf::Vector2f target { player.position.x + xsteps, player.position.y + ysteps };
            //sf::Vector2f where;
            //Object collider;

            if (!player.try_move(target, blocks))
            {
                if (!ysteps)
                {
                    ysteps = gravity * distance;
                    target.y = player.position.y + ysteps;
                    player.try_move(target, blocks);
                    //return 0;
                }
            }
            //if (player.collidesAt(target, where, collider)
            //std::cerr << (player->try_move(target, blocks) ? "A" : "B");
        }

        window.clear();
        window.draw(background);
        //player->draw(window);
        window.draw(player.get_sprite());
        window.display();
    }

    delete_ptrs(blocks);
    //delete player;
}