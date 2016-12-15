#include "state.h"

State::~State()
{
    reset();
}

const sf::Sprite& State::get_background() const
    { return background; }

const std::vector<const Object*>& State::get_texturated_objects() const
    { return texturated_objects; }

void State::reset()
{
    for (const auto *object : objects)
    {
        delete object;
    }
    objects.clear();
    texturated_objects.clear();
}