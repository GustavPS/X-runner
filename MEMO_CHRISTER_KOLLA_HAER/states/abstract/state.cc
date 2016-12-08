#include "state.h"

State::~State()
{
    reset();
}

sf::Sprite State::get_background() const
    { return background; }

std::vector<Object*> State::get_texturated_objects() const
    { return texturated_objects; }

void State::reset()
{
    for (auto object : objects)
    {
        delete object;
    }
    objects.clear();
    texturated_objects.clear();
}