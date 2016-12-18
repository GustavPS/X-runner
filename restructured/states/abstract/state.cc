#include "state.h"

State::~State()
{
    for (auto &kv : textures)
        delete kv.second;

    for (auto *object : objects)
        delete object;
}

const sf::Sprite& State::get_background() const
    { return background; }

const std::vector<const Object*>& State::get_texturated_objects() const
    { return texturated_objects; }

std::unordered_map<std::string, sf::Text>& State::ref_text_objects()
    { return text_objects; }

void State::soft_reset()
{
    for (auto *object : objects)
        delete object;
    objects.clear();
    texturated_objects.clear();
}