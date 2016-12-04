#include <cmath>

#include "player.h"

Player::Player(const sf::Vector2f &position, const sf::Vector2f &dimensions, int gid, const std::string &name)
    : Object { position, dimensions, name }
    , gid { gid }
{
    texture.loadFromFile("player.png");
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

/*Player::Player(const Player *rhs)
    : Player { rhs->position, rhs->dimensions, rhs->gid, rhs->name }
{
    delete rhs;
}*/

sf::Sprite Player::get_sprite() const
{
    return sprite;
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

bool Player::try_move(const sf::Vector2f &to, const std::vector<Object*> &objects)
{
    // perform an inexpensive computation with <will_not_collide()> before making these more expensive computations
    /*if (will_not_collide(from, to)) {
        return false;
    }*/

    // calculate the difference between <to> and <this> x-wise and y-wise
    const float x_diff { to.x - position.x };
    const float y_diff { to.y - position.y };

    // link <longest> to the longest axis
    const float& longest { std::abs(x_diff) > std::abs(y_diff) ? x_diff : y_diff };

    while (position.x != to.x || position.y != to.y)
    {
        position.x += x_diff / std::abs(longest);
        position.y += y_diff / std::abs(longest);
        sprite.setPosition(position);

        for (const auto object : objects)
        {
            if (sprite.getGlobalBounds().intersects(object->shape.getGlobalBounds()))
            {
                if (object->name == "top" || object->name == "bottom")
                    position.y -= y_diff / std::abs(longest);
                if (object->name == "side")
                    position.x -= x_diff / std::abs(longest);
                sprite.setPosition(position);
                return true;
            }
        }
    }
    return false;
}