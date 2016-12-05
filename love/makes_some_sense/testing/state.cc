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
}