#include "player.h"

Player::Player(const sf::Vector2f &position,
               const sf::Vector2f &dimensions,
               const std::vector<std::string> &types,
               float speed,
               float weight)
    : Gravitable { position, dimensions, types, speed, weight }
{
    sf::Texture txt;
    txt.loadFromFile("player.png");
    shape.setTexture( new sf::Texture { txt } );
    // do some stuff, like texture of shape.
}

#include <iostream>
#include <iomanip>
#include <math.h>
void Player::accelerate_jump()
{
    if (jump_steps != -24)
    {
        std::cerr << std::fixed << std::setprecision(20) << jump_steps << " " << (jump_steps != -2.4 ? "!= -2.4" : "== 2.4") << "\n";
        //std::cerr << jump_steps << " ";
        jump_steps -= 3;
    }
    else
    {
        should_accelerate_jump = false;
    }
}

void Player::simulate(float distance_modifier,
              float gravity_modifier,
              std::vector<Object*> &objects)
{
    // Gravitate me!
    Gravitable::simulate(distance_modifier, gravity_modifier, objects);

    // Where do I move?
    sf::Vector2f distance;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        distance.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        distance.x = 1;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     && on_ground && !on_quicksand)
    {
        should_accelerate_jump = true;
    }
    if(should_accelerate_jump)
    {
        accelerate_jump();
    }
    else if (jump_steps != 0)
    {
       // std::cerr << jump_steps;
        jump_steps += 3;
    }

    // Speed modifying debuffs
    float speed_modifier {1};

    if (on_quicksand)
        speed_modifier *= 0.75;

    if (slow_bird_count > 0)
    {
        if (slow_bird_clock.getElapsedTime().asSeconds() < 5)
        {
            speed_modifier *= 0.75 * slow_bird_count;
        }
        else
        {
            slow_bird_count = 0;
        }
    }

    if (boost_bird_count > 0)
    {
        if (boost_bird_clock.getElapsedTime().asSeconds() < 5)
        {
            speed_modifier *= 1.25 * boost_bird_count;
        }
        else
        {
            boost_bird_count = 0;
        }
    }

    if (nfbb_clock.getElapsedTime().asSeconds() < 2)
        speed_modifier = 0;
    

    // Execute move
    distance.x *= speed * speed_modifier * distance_modifier;
    distance.y = (jump_steps / 10) * speed * speed_modifier * distance_modifier;
    move(distance, objects);
}

void Player::handle_collision(Object *&object, const sf::Vector2f &steps)
{
    auto _types { object->get_types() };

    std::string _type { _types.at(0) };

    std::string _subtype;
    if (_types.size() > 1)
        _subtype = _types.at(1); 

    /*Collision with types*/
    if (_type == "ground" && steps.y > 0
     && collided_object_types.find(_type) == collided_object_types.end())
    {
        count = 1;
        on_ground = true;
        set_position(position.x, position.y - steps.y);
        collided_object_types.insert(_type);
    }
    else if (_type == "roof" && steps.y < 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x, position.y - steps.y);
        collided_object_types.insert(_type);
    }
    else if (_type == "wall" && steps.x != 0
          && collided_object_types.find(_type) == collided_object_types.end())
    {
        set_position(position.x - steps.x, position.y);
        collided_object_types.insert(_type);
    }
    else if (_type == "slow_bird")
    {
        ++slow_bird_count;
        slow_bird_clock.restart();
        collided_object_types.insert(_type);
    }
    else if (_type == "boost_bird")
    {
        ++boost_bird_count;
        boost_bird_clock.restart();
        collided_object_types.insert(_type);
    }
    else if (_type == "nfbb")
    {
        delete object;
        object = nullptr;
        nfbb_clock.restart();
        collided_object_types.insert(_type);
    }

    /*Collision with subtypes*/
    if (_subtype == "quicksand" && steps.y > 0)
    {
        on_quicksand = true;
        collided_object_types.insert(_subtype);
    }
}

void Player::handle_end_collision()
{
    /*Collision has not occured with <x>*/
    if (collided_object_types.find("ground") == collided_object_types.end())
    {
        on_ground = false;
    }
    if (collided_object_types.find("quicksand") == collided_object_types.end())
    {
        on_quicksand = false;
    }
}

void Player::handle_null_collision()
{
    on_ground = false;
    on_quicksand = false;
}
