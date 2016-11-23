#include <iostream>
#include "SFML/Graphics.hpp"
#include "classes/Player.h"
#include "classes/Block.h"
#include "classes/Platform.h"
#include "classes/Collision.h"

int main() {
    sf::Clock clock;
    sf::Time delta;

    float speed {250};
    float gravity {0.1};
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Hello World!");
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Player player {1000, 500};
    Player player2 {1200, 600};

    Platform platform {1000, 1000};

    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});
    platform.add_block(Block{100, 100});

    float addX {};
    float addY {};

    sf::Texture texture;
    if(!texture.loadFromFile("/home/gustav/ClionProjects/SFML/bg.jpg")) {
        std::cout << "hittade inte filen.";
    }
    sf::Sprite background(texture);

    sf::View view(sf::FloatRect(0, 0, 1024, 768));

    sf::View minimap(sf::FloatRect(0, 0, 2048, 1536));
    minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

    Collision collision_handler;

    bool jumping = false;
    bool left = false;
    bool right = false;
    while(window.isOpen())
    {
        /*
        if(player.getY() > 800 && addY > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ((left || right) || (addX > 0 || addX < 0)))
        {
            addY = 0;
            speed += 50;
            jumping = true;

        }
        else if(player.getY() > 800)
        {
            addY = 0;
            speed = 250;
        }
        else
        {
            addY += gravity;
        }
         */

        if(collision_handler.check_collision(player, platform) && addY > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ((left || right) || (addX > 0 || addX < 0)))
        {
            addY = 0;
            speed += 50;
            jumping = true;
        }
        else if(collision_handler.check_collision(player, platform))
        {
            addY = 0;
            speed = 250;
        } else
        {
            addY += gravity;
        }
        // move the view at point (200, 200)
        view.setCenter(player.getX() + 50, player.getY() + 50);
        minimap.setCenter(player.getX() + 50, player.getY() + 50);
        // move the view by an offset of (100, 100) (so its final position is (300, 300))

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

        // Movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            left = true;
            right = false;
        }
        else
        {
            left = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            right = true;
            left = false;
        }
        else
        {
            right = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(addY == 0)
                jumping = true;
        }

        if(left)
        {
            if(addX > -2)
            {
                addX -= 0.5;
            }

        }
        if(right)
        {
            if(addX < 2)
            {
                addX += 0.5;
            }
        }

        if(jumping)
        {
            if(addY > -3)
            {
                addY -= 0.8;
            }
            if(addY <= -3)
            {
                jumping = false;
            }
        }

        if(addX > 0.5 && !right)
            addX -= gravity;
        else if (addX < -0.5 && !left)
            addX += gravity;
        else if(!left && !right)
            addX = 0;

        delta = clock.restart();
        window.clear();
        {
            float distance = speed * (delta.asMilliseconds() / 1000.0f);
            player.move(distance * addX, distance * addY);
        }

        if(player.getShape().getGlobalBounds().intersects(player2.getShape().getGlobalBounds()))
        {
            addX = 0;
            addY = 0;
        }
        window.setView(view);

        window.draw(background);
        player.draw(window);
        player2.draw(window);
        platform.draw_horizontal(window);

        window.setView(minimap);
        window.draw(background);
        player.draw(window);
        player2.draw(window);
        platform.draw_horizontal(window);


        window.display();

    }

    return 0;
}