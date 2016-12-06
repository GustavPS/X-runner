#include <SFML/Graphics.hpp>
#include "level_parser/level_parser.h"
#include "objects/player.h"
#include "objects/block.h"
#include "objects/NPC.h"
#include "objects/slow_bird.h"

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

    Slow_Bird bird{sf::Vector2f{50, 50}, sf::Vector2f{10, 10}, "Bird"};

    sf::RenderWindow window(sf::VideoMode(1440, 960), "Hello World!");
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::FloatRect(0, 0, 1440, 960));
    view.zoom(0.3f);
    float speed {125};
    float gravity {0.13};
    

    sf::Texture bgTexture;
    bgTexture.loadFromFile("new.png");
    sf::Sprite background { bgTexture };
    // background.setScale(2, 2);

    Level_Parser level_parser { "new.tmx" };

    std::vector<Object*> blocks { level_parser.get_blocks() };
    std::vector<Slow_Bird*> slow_birds { level_parser.get_slow_birds()};
    Player player { level_parser.get_player() };
    //Player *player { new Player { level_parser.get_player() } };
    float ysteps {};
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            xsteps -= 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            xsteps += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.can_jump)
        {
            player.jumping = true;
            player.can_jump = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        

        sf::Time delta { clock.restart() };
        {
            float distance { speed * (delta.asMilliseconds() / 1000.0f) };
            float bird_distance { bird.get_speed() * (delta.asMilliseconds() / 1000.0f) };
            //sf::Vector2f where;
            //Object collider;

            
            //player.try_move(target, blocks, colliders);
            std::unordered_set<std::string> colliders;

            if (player.jumping)
            {
                if(ysteps > -2.5)
                {
                    ysteps -= 0.3;
                }
                else if(ysteps <= -2.5)
                {
                    player.jumping = false;
                }
                //ysteps -= up >= 16 ? 3.5 : up >= 8 ? 3 : 2.5;
                
                //player.try_move(target, blocks, colliders);
                //--up;
            }
            else if(player.can_jump == false)
            {
                ysteps += gravity;
            }

            for(const auto bird : slow_birds)
            {
                float bird_distance { bird->get_speed() * (delta.asMilliseconds() / 1000.0f) };
                sf::Vector2f target {bird_distance, 0};
                bird->try_move(target, blocks, colliders);
                colliders.clear();
                bird->simulate();
            }
            /*
            sf::Vector2f target {bird_distance, 0};
            bird.try_move(target, blocks, colliders);

            if(colliders.find("side") != colliders.end())
            {
                
            }
            colliders.clear();
            bird.simulate();
            */
            for(const auto bird : slow_birds)
            {
                for(const auto f : bird->get_nets())
                {
                    float net_distance { f->get_speed() * (delta.asMilliseconds() / 1000.0f) };
                    sf::Vector2f target {0, net_distance};
                    target.x = 0;
                    target.y = net_distance;
                    f->try_move(target, blocks, colliders);
                }
            }
            colliders.clear();
            sf::Vector2f target {xsteps * distance, ysteps * distance};
/*
            target.x = (xsteps * distance);
            target.y = (ysteps * distance);
*/
            //std::cerr << "ysteps: " << ysteps * distance << "\n";
            player.try_move(target, blocks, colliders);


            if(colliders.find("bottom") != colliders.end() && player.jumping == false)
            {
                ysteps = 0;
            }

            if (colliders.find("top") == colliders.end())
            {
                player.can_jump = false;
                //ysteps = gravity * distance;
                target.x = 0;
                target.y = ysteps;
                //std::cerr << "ysteps: " << ysteps << "\n";
                player.try_move(target, blocks, colliders);
            }
            else {
                //std::cerr << "bbq";
                ysteps = 0;
            }

            colliders.clear();
            //if (player.collidesAt(target, where, collider)
            //std::cerr << (player->try_move(target, blocks) ? "A" : "B");
        }

        view.setCenter(player.position.x + player.dimensions.x, player.position.y + player.dimensions.y);
        window.setView(view);
        window.clear();
        window.draw(background);
        auto s { player.get_sprite() };
        
        for(const auto bird : slow_birds)
        {
            window.draw(bird->shape);
            for(const auto net : bird->get_nets())
            {
                window.draw(net->shape);
            }
        }

        //s.setPosition(player.position.x*2, player.position.y*2);
        //s.setScale(1,1);
        window.draw(s);
        window.display();
    }

    delete_ptrs(blocks);
    //delete player;
}
