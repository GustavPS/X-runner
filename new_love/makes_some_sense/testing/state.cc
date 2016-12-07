#include "state.h"

State::State(const std::vector<Objects*> &objects)
    : objects { objects }
{}

State::~State()
{
    reset();
}

void State::reset()
{
    for (auto object : objects)
    {
        delete object;
    }
    objects.clear();
    texturated_objects.clear();
}

virtual sf::Sprite get_background() const { return background; }

virtual std::vector<Texturated_Objects*> get_texturated_objects() const
    { return texturated_objects; }