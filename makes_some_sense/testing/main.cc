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

    sf::RenderWindow window(sf::VideoMode(1440, 960), "Hello World!");
    window.setVerticalSyncEnabled(true);

    float speed {125};
    float gravity {1.25};
    

    sf::Texture bgTexture;
    bgTexture.loadFromFile("new.png");
    sf::Sprite background { bgTexture };
    background.setScale(2, 2);

    Level_Parser level_parser { "new.tmx" };

    std::vector<Object*> blocks { level_parser.get_blocks() };
    Player player { level_parser.get_player() };
    //Player *player { new Player { level_parser.get_player() } };

    int up = 0;
    sf::Clock clock;
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

        float xsteps {};
        float ysteps {};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            xsteps -= 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            xsteps += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.can_jump)
        {
            up = 24;
            player.can_jump = false;
        }

        sf::Time delta { clock.restart() };
        {
            float distance { speed * (delta.asMilliseconds() / 1000.0f) };

            //sf::Vector2f where;
            //Object collider;

            
            //player.try_move(target, blocks, colliders);
            std::unordered_set<std::string> colliders;

            if (up)
            {
                ysteps -= up >= 16 ? 3.5 : up >= 8 ? 3 : 2.5;
                //player.try_move(target, blocks, colliders);
                --up;
            }

            sf::Vector2f target { xsteps * distance, ysteps * distance };

            //std::cerr << "ysteps: " << ysteps * distance << "\n";
            player.try_move(target, blocks, colliders);

            if(colliders.find("bottom") != colliders.end())
            {
                up = 0;
            }

            if (colliders.find("top") == colliders.end())
            {
                player.can_jump = false;
                ysteps = gravity * distance;
                target.x = 0;
                target.y = ysteps;
                //std::cerr << "ysteps: " << ysteps << "\n";
                player.try_move(target, blocks, colliders);
            }
            else {
                std::cerr << "bbq";
            }

            colliders.clear();
            //if (player.collidesAt(target, where, collider)
            //std::cerr << (player->try_move(target, blocks) ? "A" : "B");
        }

        window.clear();
        window.draw(background);
        auto s { player.get_sprite() };
        s.setPosition(player.position.x*2, player.position.y*2);
        s.setScale(2,2);
        window.draw(s);
        window.display();
    }

    delete_ptrs(blocks);
    //delete player;
}